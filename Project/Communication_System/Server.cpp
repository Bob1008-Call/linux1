#include <iostream>
#include "Server.h"

using namespace std;

Server::Server()
{
  serverAddr.sin_family = PF_INET;
  serverAddr.sin_port = htons(SERVER_PORT);
  serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

  listener = 0;

  epfd = 0;
}

void Server::Init()
{
  cout<<"Init Server..." <<endl;
  //创建监听套接字
  listener = socket(PF_INET,SOCK_STREAM,0);
  if(listener < 0)
  {
    perror("listen error");
    exit(-1);
  }

  //绑定地址
  if(bind(listener,(struct sockaddr*)&serverAddr,sizeof(serverAddr) < 0))
  {
    perror("bind error");
    exit(-1);
  }

  //监听
  int ret = listen(listener,5);
  if(ret < 0)
  {
    perror("listen error");
    exit(-1);
  } 
  cout<< "Start to listen:" << SERVER_IP << endl;

  //创建事件表
  epfd = epoll_create(EPOLL_SIZE);

  if(epfd < 0)
  {
    perror("epoll_create error");
    exit(-1);
  }

  addfd(epfd,listener,true);//添加
}

void Server::Close()
{
  close(listener);

  close(epfd);
}

int Server::SendBroadcastMessage(int clientfd)
{
  char recv_buf[BUFF_SIZE];
  char send_buf[BUFF_SIZE];
  Msg msg;
  bzero(recv_buf,BUFF_SIZE);
  
  cout << "read from client(clientID = " << clientfd << ")" << endl;
  int len = recv(clientfd,recv_buf,BUFF_SIZE,0);
  
  //清空结构体，把接收到的字符串转换为结构体
  memset(&msg,0,sizeof(msg));
  memcpy(&msg,recv_buf,sizeof(msg));
  //判断接收到的信息是私聊还是群聊
  msg.fromID = clientfd;
  if(msg.content[0] == '\\' && isdigit(msg.content[1]))
  {
    msg.type = 1;
    msg.toID = msg.content[1] - '0';
    memcpy(msg.content,msg.content+2,sizeof(msg.content));
  }
  else 
  {
    msg.type = 0;
  }
  //如果客户端关闭了连接
  if(len == 0)
  {
    close(clientfd);

    clients_list.remove(clientfd);
    cout << "ClientID = " << clientfd 
         << "closed.\n now there are "
         << clients_list.size() 
         << " client in the system"
         << endl;
  }
  //发送消息给所有客户端
  else 
  {
    //判断系统是否只有一个客户端
    if(clients_list.size() == 1)
    {
      //发送提示消息
      memcpy(&msg.content,CAUTION,sizeof(msg.content));
      bzero(send_buf,BUFF_SIZE);
      memcpy(send_buf,&msg,sizeof(msg));
      send(clientfd,send_buf,sizeof(send_buf),0);
      return len;
    }

    //存放格式化后的信息
    char format_message[BUFF_SIZE];
    //群聊
    if(msg.type == 0)
    {
      //格式化发送消息的内容 #define SERVER_MESSAGE "ClientID %d say >> %s"
      sprintf(format_message,SERVER_MESSAGE,BUFF_SIZE,clientfd,msg.content);
      memcpy(msg.content,format_message,BUFF_SIZE);

      //遍历所有客户端发送消息
      list<int>::iterator it;
      for(it = clients_list.begin();it != clients_list.end();++it)
      {
        if(*it != clientfd)
        {
          bzero(send_buf,BUFF_SIZE);
          memcpy(send_buf,&msg,sizeof(msg));
          if(send(*it,send_buf,sizeof(send_buf),0) < 0)
          {
            return -1;
          }
        }
      }
    }
    //私聊
    if(msg.type == 1)
    {
      bool private_offline = true;
      sprintf(format_message,SERVER_PRIVATE_MESSAGE,clientfd,msg.content);
      memcpy(msg.content,format_message,BUFF_SIZE);
      //遍历客户端所有依次发送消息，重新判断不要给来源客户端发
      list<int>::iterator it;
      for(it = clients_list.begin(); it != clients_list.end(); ++it)
      {
        if(*it == msg.toID)
        {
          private_offline = false;
          bzero(send_buf,BUFF_SIZE);
          memcpy(send_buf,&msg,sizeof(msg));
          if(send(*it,send_buf,sizeof(send_buf),0) < 0)
          {
            return -1;
          }
        }
      }
      if(private_offline)
      {
        sprintf(format_message,SERVER_PRIVATE_ERROR_MESSAGE,msg.toID);
        memcpy(msg.content,format_message,BUFF_SIZE);
        bzero(send_buf,BUFF_SIZE);
        memcpy(send_buf,&msg,sizeof(msg));
        if(send(msg.fromID,send_buf,sizeof(send_buf),0) < 0)
        {
          return -1;
        }
      }
    }
  }
  return len;
}

void Server::Start()
{
  static struct epoll_event events[EPOLL_SIZE];

  //初始化服务器
  Init();

  //主循环
  while(1)
  {
    int epoll_event_count = epoll_wait(epfd,events,EPOLL_SIZE,-1);

    if(epoll_event_count < 0)
    {
      perror("epoll_wait error");
      break;
    }

    cout<< "epoll_event_count = \n" << epoll_event_count << endl;

    //处理这 epoll_event_count 个就绪事件
    for(int i = 0;i < epoll_event_count; ++i)
    {
      int sockfd = events[i].data.fd;
      if(sockfd == listener)
      {
        struct sockaddr_in client_address;
        socklen_t client_addrLength = sizeof(struct sockaddr_in);
        int clientfd = accept(listener,(struct sockaddr*)&client_address,&client_addrLength);

        cout << "client connection from: "
             << inet_ntoa(client_address.sin_addr) << ":"
             <<ntohs(client_address.sin_port) << ", clientfd = "
             << clientfd << endl;
        addfd(epfd,clientfd,true);

        //服务端用list保存用户连接
        clients_list.push_back(clientfd);
        cout << "Add new clientfd" << clientfd << "to epoll" << endl; 
        cout << "Now there are" << clients_list.size() << " client int the system" << endl;

        //服务端发送欢迎信息
        cout << "welcome message" << endl;
        char message[BUFF_SIZE];
        bzero(message,BUFF_SIZE);
        sprintf(message,SERVER_WELCOME,clientfd);
        int ret = send(clientfd,message,BUFF_SIZE,0);
        if(ret < 0)
        {
          perror("send error");
          Close();
          exit(-1);
        }
      }
      else 
      {
        int ret = SendBroadcastMessage(sockfd);
        if(ret < 0)
        {
          perror("error");
          Close();
          exit(-1);
        }
      }
    }
  }
  Close();
}

