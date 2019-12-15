#include <iostream>
#include <vector>
#include <algorithm>


bool haveCycles(std::vector <std::vector<bool>> &graphtable, std::vector<int> path, int n)
{
   if (path[0] == n)
       return true;
   if (std::find(path.begin(), path.end(), n) != path.end())
       return false;
   for (int i = 0; i < graphtable.size(); i++)
   {
       if (graphtable[n][i])
       {
           std::vector<int> path1 (path.size() + 1);
           for (int j = 0; j < path.size(); j++)
               path1[j] = path[j];
           path1[path.size()] = n;
           if (haveCycles(graphtable, path1, i))
               return true;
       }
   }
   return false;
}

std::vector <int> getCycles(std::vector <std::vector<bool>> &graphtable, std::vector <int> path)
{
    for (int i = 0; i < graphtable.size(); i++)
    {
        if (graphtable[path[path.size() - 1]][i])
        {
            std::vector<int> path1 (path.size() + 1);
            for (int j = 0; j < path.size(); j++)
                path1[j] = path[j];
            path1[path.size()] = i;
             if (i != path[0])
             {
                 if (haveCycles(graphtable, path, i))
                     return getCycles(graphtable, path1);
             }
             else
                 return path;
        }
    }
    return path;
}

int count (std::vector<std::vector<bool>> &graphtable)
{
    for (int j=0; j < graphtable.size(); j++)
    {
       std::vector <int> path = {j};
       for (int i = 0; i < graphtable.size(); i++)
       {
           if (graphtable[j][i] && haveCycles(graphtable, path, i))
               return j;
       }
    }
    return -1;
}

int main()
{
    int V, E;
    std::cin >> V >> E;
    if (!E)
    {
        std::cout<<"No cycles";
        return 0;
    }
    std::vector <std::vector <bool>> graphtable (V, std::vector<bool>(E));
    for (int i = 0; i < E; i++)
    {
        int a,b;
        std::cin >> a >> b;
        graphtable[a][b] = true;
    }
    
    int c = count(graphtable);
    if (c != -1)
    {
        std::vector <int> p = {c};
        std::cout<<"Cycle:\n";
        auto answer = getCycles(graphtable, p);
        for (int i : answer)
            std::cout<< i <<" ";
        std::cout<<"\n";
    }
    
    else
    {
        std::cout << "No cycles";
    }


}
