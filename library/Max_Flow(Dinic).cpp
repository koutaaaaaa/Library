struct Flow{
	struct edge {ll to, cap, rev; };
	vector<vector<edge>> G;
    vector<int> level;
    vector<int> iter;
	int MAX_V;
 
	Flow(int v){
		G.resize(v);
		iter.resize(v);
        level.resize(v , -1);
		MAX_V = v;
	}
 
	void add_edge(int from, int to, ll cap){
		G[from].push_back(edge{to, cap, (ll)G[to].size()});
		G[to].push_back(edge{from, 0, (ll)G[from].size()-1});
	};
 
    void bfs(int s){
        for(int i = 0; i < MAX_V; i++)level[i] = -1;
        queue<int> que;
        que.push(s);
        level[s] = 0;
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(int i = 0; i < G[v].size(); i++){
                edge &e = G[v][i];
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }
 
	ll dfs(int v, int t, ll f){
		if(v == t)return f;
		for(int &i = iter[v]; i < G[v].size(); i++){
			edge &e = G[v][i];
			if(e.cap > 0 && level[v] < level[e.to]){
				ll d = dfs(e.to, t, min(f, e.cap));
				if(d > 0){
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}
 
	ll max_flow(int s, int t){
		ll flow = 0;
		while(1){
			bfs(s);
			if(level[t] < 0)return flow;
            for(int i = 0; i < MAX_V; i++)iter[i] = 0;
			ll f;
            while((f = dfs(s , t , INF)) > 0)flow += f;
		}
		return 0;
	}
};