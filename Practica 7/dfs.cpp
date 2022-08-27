
DFS( Graph g, Vertex start ){
  for( auto v : g ){
    v.color = black;
    v.pred = "Nil";
    v.discovery_time = 0;
    v.finish_time = 0;
  }
  time = 0;
  dfs_traverse( g, start, time );
}

dfs_traverse( Graph g , Vertex v, int time ){
  ++time;
  v.discovery_time = time;
  v.color = "gray";
  for( u : v.get_neighbors()){
    Si u == black{
      u.pred = v;
      dfs_traverse( g, u, time )
    }
  }
  v.color = "white";
  ++time;
  v.finish_time = time;
}
