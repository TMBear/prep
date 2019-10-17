// https://leetcode.com/problems/shortest-path-with-alternating-colors/
#include <iostream>
#include <vector>
#include <deque>
#include <map>


class Solution {
protected:
  struct Node {
    int redDistance = -1;
    int blueDistance = -1;

    int getMinDistance() const {
      if (redDistance == -1)
        return blueDistance;
      if (blueDistance == -1)
        return redDistance;

      return std::min(blueDistance, redDistance);
    }
  };

  using Edges = std::map<int, std::vector<int>>;
  
public:
  std::vector<int> shortestAlternatingPaths(int n, std::vector<std::vector<int>>& red_edges, std::vector<std::vector<int>>& blue_edges);

protected:
  // Returns nodes that were updated
  std::vector<int> processNode(int nodeId, bool isBlue);

  static Edges prepareEdges(const std::vector<std::vector<int>>& edges);

  bool tryRelax(Node& node, bool isBlue, int distance);


  std::vector<Node> m_nodes;
  Edges m_blueEdges;
  Edges m_redEdges;
};


bool Solution::tryRelax(Node& node, bool isBlue, int newDistance){
  int& curDistance = isBlue ? node.blueDistance : node.redDistance;

  if (curDistance != -1 && curDistance <= newDistance)
    return false;

  curDistance = newDistance;
  return true;
}


std::vector<int> Solution::processNode(int nodeId, bool isBlue) {
  const Node& node = m_nodes[nodeId];
  int curDistance = isBlue ? node.blueDistance : node.redDistance;
  if (curDistance == -1)
    return {};

  const auto& edges = isBlue ? m_redEdges[nodeId] : m_blueEdges[nodeId];

  std::vector<int> result;
  for (int e : edges) {
    if (tryRelax(m_nodes[e], !isBlue, curDistance + 1))
        result.push_back(e);
  }
  
  return result;
}


Solution::Edges Solution::prepareEdges(const std::vector<std::vector<int>>& edges){
  Edges result;
  for (const auto& edge  : edges)
    result[edge[0]].push_back(edge[1]);
  return result;
}


std::vector<int> Solution::shortestAlternatingPaths(int n, std::vector<std::vector<int>>& red_edges, std::vector<std::vector<int>>& blue_edges) {
  m_nodes.resize(n);
  m_nodes[0].blueDistance = 0;
  m_nodes[0].redDistance = 0;

  m_blueEdges = prepareEdges(blue_edges);
  m_redEdges = prepareEdges(red_edges);

  std::deque<int> nodesToVisit;
  nodesToVisit.push_back(0);

  while (!nodesToVisit.empty()) {
    int curNode = nodesToVisit.front();
    nodesToVisit.pop_front();
    auto updatedNodes = processNode(curNode, false);
    std::copy(updatedNodes.begin(), updatedNodes.end(), std::back_inserter(nodesToVisit));

    updatedNodes = processNode(curNode, true);
    std::copy(updatedNodes.begin(), updatedNodes.end(), std::back_inserter(nodesToVisit));
  }

  std::vector<int> result;
  result.reserve(n);
  for (const auto node : m_nodes)
    result.push_back(node.getMinDistance());

  return result;
}


static void test() {
  {
    std::vector<std::vector<int>> redNodes = {{0,1}, {1,2}};
    std::vector<std::vector<int>> blueNodes = {};

    Solution s;
    auto res = s.shortestAlternatingPaths(3, redNodes, blueNodes);
    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;
  }
  {
    std::vector<std::vector<int>> redNodes = {{0,1}};
    std::vector<std::vector<int>> blueNodes = {{2, 1}};

    Solution s;
    auto res = s.shortestAlternatingPaths(3, redNodes, blueNodes);
    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;
  }
  {
    std::vector<std::vector<int>> redNodes = {{1, 0}};
    std::vector<std::vector<int>> blueNodes = {{2, 1}};

    Solution s;
    auto res = s.shortestAlternatingPaths(3, redNodes, blueNodes);
    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;
  }

  {
    std::vector<std::vector<int>> redNodes = {{0, 1}};
    std::vector<std::vector<int>> blueNodes = {{1, 2}};

    Solution s;
    auto res = s.shortestAlternatingPaths(3, redNodes, blueNodes);
    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;
  }
  {
    std::vector<std::vector<int>> redNodes = {{0, 1}, {0, 2}};
    std::vector<std::vector<int>> blueNodes = {{1, 0}};

    Solution s;
    auto res = s.shortestAlternatingPaths(3, redNodes, blueNodes);
    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;
  }
}
