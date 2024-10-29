class DISJOINT_SET_UNION
{
private:
    vector<int> id;
    vector<vector<int>> component;
    public:
    inline DISJOINT_SET_UNION(int new_size)
    {
        for (int i = 0; i < new_size; ++i)
        {
            id.push_back(i);
            component.push_back({i});
        }
    }
    inline bool IsSameSet(int ina, int inb)
    {
        return id[ina] == id[inb];
    }
    inline void CombineSet(int ina, int inb)
    {
        if (IsSameSet(ina, inb))
        {
            return;
        }
        int bigger_id = ina, smaller_id = inb;
        if (component[bigger_id].size() > component[smaller_id].size())
        {
            swap(bigger_id, smaller_id);
        }
        for (auto & i : component[smaller_id])
        {
            id[i] = bigger_id;
            component[bigger_id].push_back(i);
        }
    }
};
