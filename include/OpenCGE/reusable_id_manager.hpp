#ifndef OPENCGE_REUSABLE_ID_MANAGER_HPP_
#define OPENCGE_REUSABLE_ID_MANAGER_HPP_

#include <stack>

class ReusableIdManager
{
public:
  size_t getId()
  {
    if(staleIds.empty())
    {
      return count++;
    }
    else
    {
      size_t id = staleIds.top();
      staleIds.pop();
      return id;
    }
  }
  void freeId(size_t id)
  {
    staleIds.push(id);
  }

private:
  size_t count;
  std::stack<size_t> staleIds;
};

#endif
