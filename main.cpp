#include <iostream>
#include <vector>
#include <queue>
 
std::pair<int, int> to_coordinates(std::string cell_name) {
    return {int(cell_name[0]) - int('a'), std::stoi(std::string(1, cell_name[1])) - 1};
}
 
std::string to_string(std::pair<int, int> coordinates) {
    return std::string(1, char(coordinates.first + int('a'))) + std::to_string(coordinates.second + 1);
}
 
bool is_on_board(std::pair<int, int> coordinates) {
    return ((coordinates.first >= 0) && (coordinates.first <= 7)) &&
           ((coordinates.second >= 0) && (coordinates.second <= 7));
}
 
std::vector<std::pair<int, int>> horse_targets(std::pair<int, int> cell) {
    std::vector<std::pair<int, int>> ans;
    if (is_on_board(std::pair(cell.first + 1, cell.second + 2))) {
        ans.emplace_back(cell.first + 1, cell.second + 2);
    }
    if (is_on_board(std::pair(cell.first + 2, cell.second + 1))) {
        ans.emplace_back(cell.first + 2, cell.second + 1);
    }
    if (is_on_board(std::pair(cell.first + 2, cell.second - 1))) {
        ans.emplace_back(cell.first + 2, cell.second - 1);
    }
    if (is_on_board(std::pair(cell.first + 1, cell.second - 2))) {
        ans.emplace_back(cell.first + 1, cell.second - 2);
    }
    if (is_on_board(std::pair(cell.first - 1, cell.second - 2))) {
        ans.emplace_back(cell.first - 1, cell.second - 2);
    }
    if (is_on_board(std::pair(cell.first - 2, cell.second - 1))) {
        ans.emplace_back(cell.first - 2, cell.second - 1);
    }
    if (is_on_board(std::pair(cell.first - 2, cell.second + 1))) {
        ans.emplace_back(cell.first - 2, cell.second + 1);
    }
    if (is_on_board(std::pair(cell.first - 1, cell.second + 2))) {
        ans.emplace_back(cell.first - 1, cell.second + 2);
    }
    return ans;
}
 
void bfs(std::pair<int, int> vertex, std::pair<int, int> target, std::vector<std::vector<std::vector<std::string>>> &dp) {
 
    std::pair<int, int> currents_vertex = vertex;
    std::queue<std::pair<int, int>> next;
 
    while (currents_vertex != target) {
        for (auto i: horse_targets(currents_vertex)) {
            if (dp[i.first][i.second].empty()) {
                dp[i.first][i.second] = dp[currents_vertex.first][currents_vertex.second];
                dp[i.first][i.second].push_back(to_string(i));
                next.push(i);
            }
        }
        currents_vertex = next.front();
        next.pop();
    }
}
 
std::vector<std::string> horse_path(std::pair<int, int> start, std::pair<int, int> finish) {
    // we do BFS here via standard dp method, refer to lectures for dp description
    std::vector<std::vector<std::vector<std::string>>> dp(8,
                                                          std::vector<std::vector<std::string>>(8,
                                                                                                std::vector<std::string>()));
 
    // here goes BFS until we update target cell
 
    dp[start.first][start.second].push_back(to_string(start));
 
    bfs(start, finish, dp);
 
    return dp[finish.first][finish.second];
}
 
 
int main() {
 
    std::pair<int, int> start;
    std::pair<int, int> finish;
 
    std::string raw_start;
    std::string raw_finish;
 
    std::cin >> raw_start >> raw_finish;
 
    start = to_coordinates(raw_start);
    finish = to_coordinates(raw_finish);
 
    for (const auto& i : horse_path(start, finish)) {
        std::cout << i << '\n';
    }
 
}
