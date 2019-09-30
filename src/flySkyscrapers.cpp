#include <iostream>
#include <vector>
#include <stack>


long long nChoosek(long long n, long long k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    long long result = n;
    for( long long i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}



struct Building {
  Building(int h, int hr, int indx)
    : height(h)
    , higherOnRightPos(hr)
    , index(indx)
  {}

  int height = -1;
  int higherOnRightPos = -1;
  int index = -1;
};



void calcHighestOnRight(std::vector<Building>& buildings) {
  if (buildings.empty())
    return;

  Building guard{std::numeric_limits<int>::max(), -1, -1};
  std::stack<Building*> st;
  st.push(&guard);

  for (auto& bldg : buildings) {
    while (st.top()->height < bldg.height) {
      st.top()->higherOnRightPos = bldg.index;
      st.pop();
    }

    st.push(&bldg);
  }

  while (!st.empty()) {
    st.top()->higherOnRightPos = std::numeric_limits<int>::max();
    st.pop();
  }
}

std::vector<Building> heightsToBuildings(const std::vector<int>& heights) {
  std::vector<Building> buildings;
  buildings.reserve(heights.size());

  for (int i = 0; i < (int)heights.size(); ++i) {
    buildings.emplace_back(heights[i], -1, i);
  }

  return buildings;
}


template <class Iter>
long long calcPathsBetweenSameHeightBuildings(const Iter& l, const Iter& r) {

  long long paths = 0;

  Iter cur = l;
  while(cur != r) {
    int furthestFromCur = cur->higherOnRightPos;
    auto furthestBldg = std::upper_bound(cur, r, furthestFromCur, [](int indx, const Building& b) {
          return indx < b.index;
        });

    // Same hegith buildings
    long long shb = furthestBldg - cur;
    paths += nChoosek(shb, 2) * 2;

    cur = furthestBldg;
  }

  return paths;
}



long long calcPaths(std::vector<Building>& buildings) {

  auto compareHeights = [](const Building& b1, const Building b2) {
    return b1.height < b2.height;
  };

  std::stable_sort(buildings.begin(), buildings.end(), compareHeights);

  long long paths = 0;
  auto l = buildings.begin();
  while (l != buildings.end()) {
    auto r = std::upper_bound(l, buildings.end(), *l, compareHeights);

    paths += calcPathsBetweenSameHeightBuildings(l, r);
    l = r;
  }

  return paths;
}




std::vector<int> readFromStdin() {
  int n = 0;
  std::cin >> n;

  std::vector<int> data;
  data.reserve(n);
  for (int i = 0; i < n; ++i) {
    int h = 0;
    std::cin >> h;
    data.push_back(h);
  }

  return data;
}

int main() {
  std::cout << "Hello World!" << std::endl;

 // std::vector<int> heights = {3, 2, 1, 2, 3, 3};
 // std::vector<int> heights = {1, 1000, 1};
 auto heights = readFromStdin();

  auto buildings = heightsToBuildings(heights);

  calcHighestOnRight(buildings);

//  for (const auto& b : buildings)
//    std::cout << b.index << " " << b.height << " " << b.higherOnRightPos << std::endl;

//  std::cout << "======================" << std::endl;

  long long paths = calcPaths(buildings);
  std::cout << "Paths: " << paths << std::endl;

}

