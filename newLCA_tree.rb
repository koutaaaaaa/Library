//g��vvl
struct LCA_tree{
public:
	ll len;
	vvl p;
	vl dep;
	LCA_tree(ll m,vvl g){
		len = m;
		p.resize((int)20);
		rep(i,0,20)p[i].resize(len);
		dep.resize(len,LINF);
		dep[0] = 0;
		queue<int> que;
		que.push(0);
		while(!que.empty()){
			int a = que.front(); que.pop();
			rep(i,0,g[a].size()){
				int c = g[a][i];
				if(dep[c] != LINF)continue;
				dep[c] = dep[a] + 1;
				que.push(c);
			}
		}
		rep(i,0,m){
			rep(j,0,g[i].size()){
				int c = g[i][j];
				if(dep[c] < dep[i])continue;
				input(c,i);
			}
		}
	}
	ll la(ll x,ll h){
		for(int i = 19;i >= 0;--i){
			if((1<<i) <= h){
				x = p[i][x];
				h -= (1<<i);
			}
		}
		return x;
	}
	ll lca(ll u,ll v){
		if(dep[u] < dep[v])swap(u,v);//dep[u] >= dep[v]
		u = la(u, dep[u] - dep[v]);
		if(u == v)return u;
		for(int i = 19; i >= 0; --i){
			if(p[i][u] != p[i][v]){
				u = p[i][u];
				v = p[i][v];
			}
		}
		return p[0][u];
	}
	void input(ll ch,ll pa){
		p[0][ch] = pa;
	}
    void tree_build(){
		//Doubling
		for(int i = 1; i < 20;i++){
			for(ll j = 0;j < len; j++){
				p[i][j] = p[i-1][p[i-1][j]];
			}
		}
	}
};