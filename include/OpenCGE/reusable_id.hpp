#ifndef INCLUDE_OPENCGE_REUSABLE_ID_HPP_
#define INCLUDE_OPENCGE_REUSABLE_ID_HPP_

#include <stack>

class ReusableId
{
public:
  size_t getId()
  {
    if(stale_ids.empty())
    {
      return id_count++;
    }
    else
    {
      size_t id = stale_ids.top();
      stale_ids.pop();
      return id;
    }
  }
  void freeId(size_t id)
  {
    stale_ids.push(id);
  }

private:
  size_t id_count;
  std::stack<size_t> stale_ids;
};

#endif /* INCLUDE_OPENCGE_REUSABLE_ID_HPP_ */
