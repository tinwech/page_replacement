/*
Student No.: 109511097
Student Name: Ting-Wei Chiang
Email: tinwech.ee09@nycu.edu.tw
SE tag: xnxcxtxuxoxsx
Statement: I am fully aware that this program is not 
supposed to be posted to a public server, such as a 
public GitHub repository or a public web page.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
#include <sys/time.h>
using namespace std;

struct Node {
    Node(uint id) : id(id) {}
    uint id;
    uint ref = 0;
    list<Node*>::const_iterator it;
};

int frame_num[] = {64, 128, 256, 512};

void LFU(char *file) {
    struct timeval start, end;
    gettimeofday(&start, 0);
    printf("LFU policy:\n");
    printf("Frame\tHit\t\tMiss\t\tPage fault ratio\n");
    for (int i = 0; i < 4; i++) {
        int miss = 0, hit = 0, size = 0;
        int min_ref;
        unordered_map<uint, Node*> hash;
        unordered_map<uint, list<Node*>> freq;
        ifstream fin;
        fin.open(file);
        uint id;
        while (fin >> id) {
            Node* cur = hash[id];
            if (!cur) { // miss
                miss++;
                if (size < frame_num[i]) {
                    size++;
                }
                else {
                    hash.erase(freq[min_ref].back()->id);
                    delete freq[min_ref].back();
                    freq[min_ref].pop_back();
                }
                cur = new Node(id);
                freq[cur->ref].push_front(cur);
                min_ref = cur->ref;
            }
            else { // hit
                hit++;
                freq[cur->ref].erase(cur->it);
                if (min_ref == cur->ref && freq[cur->ref].size() == 0) min_ref++;
                cur->ref++;
                freq[cur->ref].push_front(cur);
            }
            cur->it = freq[cur->ref].cbegin();
            hash[id] = cur;
        }
        fin.close();
        printf("%d\t%d\t\t%d\t\t%.10f\n", frame_num[i], hit, miss, (double) miss / (hit + miss));
    }
    gettimeofday(&end, 0);
    int sec = end.tv_sec - start.tv_sec;
    int usec = end.tv_usec - start.tv_usec;
    double time = sec + usec / 1000000.0;
    printf("Total elapsed time %.4f sec\n", time);
}

void LRU(char *file) {
    struct timeval start, end;
    gettimeofday(&start, 0);
    printf("LRU policy:\n");
    printf("Frame\tHit\t\tMiss\t\tPage fault ratio\n");
    for (int i = 0; i < 4; i++) {
        list<Node*> lru;
        unordered_map<uint, Node*> hash;
        int miss = 0, hit = 0;
        ifstream fin;
        fin.open(file);
        uint id;
        while (fin >> id) {
            Node* cur = hash[id];
            if (!cur) { // miss
                miss++;
                if (lru.size() == frame_num[i]) { // replace
                    hash.erase(lru.back()->id);
                    delete lru.back();
                    lru.pop_back();
                }
                cur = new Node(id);
                lru.push_front(cur);
            }
            else { // hit
                hit++;
                lru.splice(lru.begin(), lru, cur->it);
            }
            hash[id] = *lru.cbegin();
            cur->it = lru.cbegin();
        }
        fin.close();
        printf("%d\t%d\t\t%d\t\t%.10f\n", frame_num[i], hit, miss, (double) miss / (hit + miss));
    }
    gettimeofday(&end, 0);
    int sec = end.tv_sec - start.tv_sec;
    int usec = end.tv_usec - start.tv_usec;
    double time = sec + usec / 1000000.0;
    printf("Total elapsed time %.4f sec\n", time);
}

int main(int argc, char *argv[]) {
    LFU(argv[1]);
    printf("\n");
    LRU(argv[1]);
    return 0;
}