#include <iostream>
#include <vector>



using namespace std;


class Node
{
public:
    using p_int = unsigned int;
    
    p_int parentIndex = 0;
    p_int lenght = 0;
    
};

template <typename Container, typename T>
class LES
{
public:
    using p_int = Node::p_int;

    Container * cnt;
    bool (*f)(const T&, const T&);
    std::vector<Node> nodeList;
    
    LES(Container& list, bool (*f)(const T&, const T&))
        : cnt(&list), f(f), nodeList(list.size())
        {
            for (int i = 0; i < nodeList.size(); i++)
            {
                nodeList[i].parentIndex = i;
            }
        }
    
    std::vector<int> finder()
    {
        p_int max = 0;
        p_int maxIndex = 0;
        
        for (p_int i = 0; i < cnt->size(); i++)
        {
            for (p_int j = i + 1; j < cnt->size(); j++)
            {
                if ( nodeList[i].lenght + 1 > nodeList[j].lenght )
                {
                    if (f( (*cnt)[i], (*cnt)[j] ))
                    {
                        nodeList[j].lenght = nodeList[i].lenght + 1;
                        nodeList[j].parentIndex = i;
                    }
                }
            }
            if (nodeList[i].lenght > max)
            {
                max = nodeList[i].lenght;
                maxIndex = i;
            }
        }
        std::vector<int> indexList;
        do
        {
            indexList.push_back(maxIndex);
            maxIndex = nodeList[maxIndex].parentIndex;
        }
        while (maxIndex != nodeList[maxIndex].parentIndex);
        indexList.push_back(maxIndex);
        return indexList;
    }
};


std::vector<int> liste = {
    3,1,8,2,5,9
};


int main()
{
    LES<std::vector<int>, int> sinif(liste, [](const int& x, const int& y){return x < y;});
    auto x = sinif.finder();
    cout << "[";
    for (auto y = x.rbegin(); y != x.rend(); y++)
    {
        cout << liste[*y] << ",";
    }
    cout << "\b]" << endl;
    return 0;
}
