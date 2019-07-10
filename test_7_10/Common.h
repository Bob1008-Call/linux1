#define size_t int
size_t BKDRHash(const char* str)
{
  unsigned int seed = 131;
  unsigned int hash = 0;
  while(*str)
  {
    hash = hash * seed + (*str++);
  }
  return (hash & 0x7FFFFFFF);
}

size_t SDBMHash(const char* str)
{
  size_t hash = 0;
  while(size_t ch = (size_t)*str++)
  {
    hash = 65599*hash+ch;
  }
  return hash;
}

size_t RSHash(const char* str)
{
  size_t hash = 0;
  size_t magic = 63689;
  while(size_t ch = (size_t)*str++)
  {
    hash = hash * magic + ch;
    magic *= 378551;
  }
  return hash;
}

size_t APHash(const char* str)
{
  size_t hash = 0;
  size_t ch;
  for(long i = 0;ch = (size_t)*str++;++i)
  {
    if(0 == (i&1))
    {
      hash ^= ((hash << 7) ^ (hash >> 3));
    }
    else 
    {
      hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
    }
  }
  return hash;
}

size_t JSHash(const char* str)
{
  if(!*str)
  {
    return 0;
  }
  size_t hash = 1315423911;
  while(size_t ch = (size_t)*str++)
  {
    hash ^= ((hash << 5) + ch + (hash >> 2));
  }
  return hash;
}

template<class K>
struct _Fun1
{
  size_t operator()(const K& key)
  {
    return BKDRHash(key.c_str());
  }
};

template<class K>
struct _Fun2
{
  size_t operator()(const K& key)
  {
    return BKDRHash(key.c_str());
  }
};

template<typename K>
struct _Fun3
{
    size_t operator()(const K& key)
    {
        return RSHash(key.c_str());
    }
};

template<typename K>
struct _Fun4
{
    size_t operator()(const K& key)
    {
        return APHash(key.c_str());
    }
};

template<typename K>
struct _Fun5
{
    size_t operator()(const K& key)
    {
        return JSHash(key.c_str());
    }
};
