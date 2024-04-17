import networkx as nx
from pyvis.network import Network

# F_u = u points to v
# B_u = v points to u
# N_u = number of outgoing links from u
# c = normalization factor

def read_graph(filename):
    graph = nx.DiGraph()
    with open(filename, 'r') as f:
        for _ in range(4): f.readline()
        for line in f:
            u, v = line.strip().split()
            graph.add_edge(int(u), int(v))
    for i in range(0, len(graph.nodes)):
        if i not in graph.nodes:
            graph.add_node(i)
            print(f"Adding node {i}")
    return graph

def rgb_to_hex(rgb):
    return '#{:02x}{:02x}{:02x}'.format(*rgb)

def get_node_color(value, max_value):
    low = (127, 255, 0) # light green
    high = (100, 11, 11) # dark red
    factor = abs(value / max_value)
    interpolated_rgb = tuple(int(part[0] * (1 - factor) + part[1] * factor) for part in zip(low, high))
    return rgb_to_hex(interpolated_rgb)

def show_graph(graph, pagerank, title):
    BLACK = "000000"
    V = len(graph.nodes)
    
    max_rank = max(pagerank.values())
    g = Network(directed=True)
    g.add_nodes([i for i in range(V)],
                size=[5 for i in range(V)],
                color=[get_node_color(pagerank[u], max_rank) for u, graph in graph.nodes(data=True)])
    for a, b in graph.edges:
        g.add_edge(int(a), int(b), color=BLACK)
    g.show(f"{title}.html")

if __name__ == '__main__':
    #graph = read_graph('p2p-Gnutella04.txt')
    # directed graph generated with 20 nodes
    #graph = nx.random_k_out_graph(20, 3, 0.5)
    graph = nx.gn_graph(50)
    pr = nx.pagerank(graph, alpha=0.85)
    #nx.draw_networkx(graph, with_labels=True)
    show_graph(graph, pr, "mine")