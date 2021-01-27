#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct music{
    int id;
    int num;
    bool operator< (const music a) const{
        if(num == a.num) return id > a.id;
        return num > a.num;
    }
};

struct genre_node{
    int sum;
    string name;
    vector<music> music_list;
    bool operator< (const genre_node a) const{
        return sum > a.sum;
    }
};
#include <iostream>
vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    int size = genres.size();
    vector<genre_node> genres_list;
    map<string, int> genres_map;
    int idx = 1;
    for(int i=0;i<size;i++){
        if( genres_map[genres[i]] == 0 ){
            genres_map[genres[i]] = idx++;
            genre_node tmp;
            tmp.name = genres[i];
            tmp.sum = plays[i];
            music tmp2;
            tmp2.id = i;
            tmp2.num = plays[i];
            tmp.music_list.push_back(tmp2);
            genres_list.push_back(tmp);
        }
        else{
            int g_idx = genres_map[ genres[i] ] - 1;
            genre_node& tmp = genres_list[g_idx];
            tmp.sum += plays[i];
            tmp.music_list.push_back({i, plays[i]});
        }
    }
    sort( genres_list.begin(), genres_list.end() );
    for(int i=0;i<genres_list.size();i++){
        genre_node tmp = genres_list[i];
        sort(tmp.music_list.begin(), tmp.music_list.end());
        int list_size = tmp.music_list.size();
        for(int j=0;j< min(2, list_size );j++ ){
            answer.push_back(tmp.music_list[j].id);
        }
    }
    return answer;
}

int main(){

    auto ret = solution({"clas", "pop", "clas", "clas", "pop"}, {500,600,150,800,2500});
    auto ret2 = solution({"clas1", "pop2", "clas3", "clas4", "pop5"}, {500,600,150,800,2500});

    int a = 2;
    return 0;
}