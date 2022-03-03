#include <vector>
#include <iostream>
#include <numeric>
#include <iterator>

using namespace std;

struct segment_tree {
    vector<int> arr;
    vector<int> tree;

    segment_tree(vector<int> arr): arr(arr) {
        tree.resize(2*arr.size() + 1);
        buildSegmentTree(1, 0, arr.size()-1);
    }

    void buildSegmentTree(int treeIndex, int rangeLeft, int rangeRight) {
        //cout << rangeLeft << " " << rangeRight << " \n";
        if(rangeLeft >= rangeRight) {
            tree[treeIndex] = arr[rangeLeft];
            return;
        }
        int rangeMid = (rangeLeft + rangeRight) / 2;
        buildSegmentTree(treeIndex*2, rangeLeft, rangeMid);
        buildSegmentTree(treeIndex*2 + 1, rangeMid+1, rangeRight);
        tree[treeIndex] = tree[treeIndex*2] + tree[treeIndex*2 + 1];
    }

    int getSumInternal(int treeIndex, 
                       int rangeLeft, 
                       int rangeRight, 
                       int targetRangeLeft, 
                       int targetRangeRight) {
        if(rangeLeft == targetRangeLeft && rangeRight == targetRangeRight) {
            return tree[treeIndex];
        }
        int rangeMid = (rangeLeft + rangeRight) / 2;
        if(targetRangeRight <= rangeMid) {
            return getSumInternal(2*treeIndex, rangeLeft, rangeMid, targetRangeLeft, targetRangeRight);
        } else if(targetRangeLeft > rangeMid) {
            return getSumInternal(2*treeIndex + 1, rangeMid+1, rangeRight, targetRangeLeft, targetRangeRight);
        } else {
            return getSumInternal(2*treeIndex, rangeLeft, rangeMid, targetRangeLeft, rangeMid) +
                   getSumInternal(2*treeIndex + 1, rangeMid+1, rangeRight, rangeMid+1, targetRangeRight);
        }
    }

    int getSum(int targetRangeLeft, int targetRangeRight) {
        return getSumInternal(1, 0, arr.size()-1, targetRangeLeft, targetRangeRight);
    }
};

void test(vector<int> &arr, segment_tree &st, int left, int right) {
    int rightAns = accumulate(arr.begin()+left, arr.begin()+right+1, 0), obtainedAns = st.getSum(left, right);
    cout << "Expected: " << rightAns << " get: " << obtainedAns << "\n";
}

int main() {
    vector<int> arr {0, 1,2,3,4,5,6,7,8};
    segment_tree st(arr);
    copy(st.tree.begin(), st.tree.end(), ostream_iterator<int>(cout, " "));
    cout << " \n";
    test(arr, st, 0, 0);
    test(arr, st, 1, 1);
    test(arr, st, 0, 7);
    test(arr, st, 3, 5);
    return 0;
}