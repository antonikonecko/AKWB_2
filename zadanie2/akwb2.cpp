#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include<map>


// CHANGE INFILE NAME BEFORE STARTING 
//std::string infile = "1";
std::string infile;
std::string outfile = "output/" + infile + "_out.txt";

std::map <int, std::vector<int>> adj_list_G;
std::vector<std::pair<int, int>> edges_G;
std::vector<std::pair<int, int>> edges_H;
std::vector<std::vector<int>> edge_list_H;
//std::vector<std::vector<int>> edges_G;

void adj_list_to_edges(std::map <int, std::vector<int>> graph) {
	/*std::vector<std::pair<int, int>> edges_G;*/
	std::vector<int> temp;

	for (auto it = graph.cbegin(); it != graph.cend(); ++it) {	
		for (auto& successor : it->second) { 
			
			int predecessor = it->first;		
			std::pair<int, int> edge = std::pair<int, int>(predecessor, successor);		
			edges_G.push_back(edge);
		}
	}		
	
}

void vec_of_vec_to_vec_of_pair(std::vector<std::vector<int>> vec_of_vec) {
	
	for (int i = 0; i < vec_of_vec.size(); i++) {		
		int start_vert = vec_of_vec[i][0];
		int end_vert = vec_of_vec[i][1];
		std::pair<int, int> edge = std::pair<int, int>(start_vert, end_vert);
		edges_H.push_back(edge);
	}
}


void save_dot_format(std::vector<std::pair<int, int>> edges, std::string graph_name) {
	std::string dotfile = "dot/" + graph_name + "_" + infile + ".dot";
	std::ofstream dot_file;
	dot_file.open(dotfile);
	if (dot_file.good() == true) {
		dot_file << "digraph {" << std::endl;
		/*dot_file << "landscape=true" << std::endl;*/
		int i = 1;
		//for (auto it = edges.begin(); it != edges.end(); it++) {
		//	if(graph_name == "H")
		//	dot_file << it->first << " -> " << it->second << " [label = " << '"' << i << '"' << ']' << std::endl;
		//	else {
		//		dot_file << it->first << " -> " << it->second << std::endl;
		//	}	
		//	i++;
		//}
		if (graph_name == "G") {
			for (auto it = adj_list_G.cbegin(); it != adj_list_G.cend(); ++it) {
				if (!it->second.empty()) {
					for (auto& successor : it->second) {
						int predecessor = it->first;
						dot_file << it->first << " -> " << successor << std::endl;
					}
				}
				else {
					dot_file << it->first << std::endl;
				}		
			}
		}
		else if (graph_name == "H") {
			for (auto it = edges.cbegin(); it != edges.cend(); it++) {
				dot_file << it->first << " -> " << it->second << " [label = " << '"' << i << '"' << ']' << std::endl;
				i++;
			}
		}
		dot_file << "}";
		std::cout << std::endl;
		std::cout << "DOT file saved"<< dotfile << std::endl;
	}
	else {
		std::cout << "Error! Cannot save file." << std::endl;
	}
	dot_file.close();
}


void read_graph_from_file(std::string infile) {
	std::string infile_path = "input/" + infile + ".txt";
	std::ifstream read_file(infile_path.c_str());
	if (read_file.fail()) {
		std::cerr << "Cannot open file! " << infile << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Reading file: " << infile << std::endl;
	std::cout << std::endl;
	std::string line;
	while (std::getline(read_file, line)) {
		std::istringstream ss_line(line);
		std::vector<int> curr_vertex_succesors;
		std::vector<int> vertexes;
		int v;
		int curr_vertex = 0;
		int char_position = 0;
		while (ss_line >> v) {
			if (char_position == 0) {
				curr_vertex = v;
			}
			else {
				curr_vertex_succesors.push_back(v);
			}
			char_position++;
		}		
		//std::sort(curr_vertex_succesors.begin(), curr_vertex_succesors.end());
		adj_list_G.insert(std::pair<int, std::vector<int>>(curr_vertex, curr_vertex_succesors));

	}
	read_file.close();
}


void print_curr_vertex_successors(std::map <int, std::vector<int>> graph, int vertex_id) {
	std::cout << std::endl;
	auto it = graph.find(vertex_id);
	std::cout << it->first << ": ";
	for (auto successor = it->second.cbegin(); successor != it->second.cend(); ++successor) {
		std::cout << *successor << " ";
	}
}


void print_graph(std::map <int, std::vector<int>> graph) {
	for (auto it = graph.cbegin(); it != graph.cend(); ++it)
	{
		std::cout << it->first << ": ";
		for (auto successor = it->second.cbegin(); successor != it->second.cend(); ++successor) {
			std::cout << *successor << " ";
		}
		std::cout << std::endl;
	}
}


void save_to_file(int h_iter, std::string outfile, std::map <int, std::vector<int>> graph) {
	std::cout << std::endl;
	std::cout << "--------------- " << std::endl;
	std::cout << "graph H: " << std::endl;
	std::ofstream out_file;
	out_file.open(outfile);
	if (out_file.good() == true) {
		//print vertices
		for (int i = 1; i < h_iter; i++) {
			out_file << i << " ";
			std::cout << i << ": ";
			//print successors
			for (int j = 0; j < graph.size(); j++) {
				if (edge_list_H[j][0] == i) {
					out_file << edge_list_H[j][1] << " ";
					std::cout << edge_list_H[j][1] << " ";
				}
			}
			out_file << "\n";
			std::cout << std::endl;
		}
		std::cout << "--------------- " << std::endl;
		std::cout << std::endl;
		std::cout << "File saved: " << outfile << std::endl;
	}
	else {
		std::cout << "Error! file cannot be saved" << std::endl;
	}

}


void print_vector_of_vector(std::vector<std::vector<int>> vec_of_vec) {
	for (const auto& row : vec_of_vec) {
		for (const auto& node : row) {
			std::cout << node << ' ';
		}
		std::cout << std::endl;
	}
}


void print_transf(std::map <int, std::vector<int>> graph) {
	std::cout << "V(G)	E(H)" << std::endl;
	for (int i = 0; i < graph.size(); i++) {
		std::cout << i + 1 << "	";
		for (int j = 0; j < edge_list_H[i].size(); j++) {
			std::cout << edge_list_H[i][j] << "  ";
		}
		std::cout << std::endl;
	}

}


void transform(std::map <int, std::vector<int>> graph) {
	std::cout << std::endl;
	std::cout << "***TRANSFORMATION*** " << std::endl;
	std::cout << std::endl;
	int start_vert = 1;
	int vertG_succ, edgeH_start_vert, edgeH_end_vert;
	/*
	create edge list - each vert in G is transformed into edge in H 
		 V(G)1 -> E(H)1 2 
		 V(G)2 -> E(H)3 4 
		 V(G)3 -> E(H)5 6
	 */
	for (auto vert = graph.cbegin(); vert != graph.cend(); ++vert) {
		int end_vert = vert->first * 2;		
		std::vector<int>list;
		list.push_back(start_vert);
		list.push_back(end_vert);
		edge_list_H.push_back(list);
		start_vert += 2;
	}
	/*std::cout << std::endl;
	std::cout << "############" << std::endl;
	print_transf(graph);
	std::cout << "############" << std::endl;*/
	for (auto vert = graph.cbegin(); vert != graph.cend(); ++vert) {
		int vert_G = vert->first;
		for (auto succ = vert->second.cbegin(); succ != vert->second.cend(); ++succ) {
			vertG_succ = *succ;			
			edgeH_start_vert = edge_list_H[vertG_succ - 1][0];	  	
			edgeH_end_vert = edge_list_H[vert_G - 1][1];	     
			edge_list_H[vertG_succ - 1][0] = edgeH_end_vert; 
			for (int it = 0; it < graph.size(); it++) {
				if (edge_list_H[it][0] == edgeH_start_vert) {
					edge_list_H[it][0] = edgeH_end_vert;
				}
				if (edge_list_H[it][1] == edgeH_start_vert) {
					edge_list_H[it][1] = edgeH_end_vert;
				}
			}
		}
	}
	/*std::cout << std::endl;
	std::cout << "*****************" << std::endl;
	print_transf(graph);
	std::cout << "*****************" << std::endl;*/

	//indexing
	int h_iter = 1;
	for (int it = 0; it < graph.size(); it++) {
		for (int n = 0; n < edge_list_H[it].size(); n++) {
			//If the component of edge n (vertex) >= hiter, then compare it with the other vertices of other edges.
			if (edge_list_H[it][n] >= h_iter) {
				int graph_H_it_n = edge_list_H[it][n];
				for (int it2 = 0; it2 < graph.size(); it2++) {
					for (int m = 0; m <= 1; m++) {
						// If a vertex in an edge is equal to another vertex, replace its value with "h_iter".
						if (edge_list_H[it2][m] == graph_H_it_n) {
							edge_list_H[it2][m] = h_iter;
						}
					}
				}
				h_iter++;
			}
		}
	}
	print_transf(graph);
	vec_of_vec_to_vec_of_pair(edge_list_H);
	save_dot_format(edges_H, "H");
	save_to_file(h_iter, outfile, graph);
}


bool linearity(std::map <int, std::vector<int>> graph) {
	/*1- Graph G is a directed linear graph only if for all pairs of its 
	vertices x and y, the following condition is satisfied:
	 N+(x) ∩ N+(y) ≠ Ø ⇒ ( N+(x) = N+(y) ∧ N–(x) ∩ N–(y) = Ø ),
		where N–(x) denotes the set of direct predecessors of x.*/
	int succ1_val, succ2_val;
	int vert_start_val = 1;
	for (auto vert_start = graph.cbegin(); vert_start != graph.cend(); ++vert_start) {		
		if (vert_start->second.size() > 1) {			
			for (auto succ1 = vert_start->second.cbegin(); succ1 != vert_start->second.cend(); ++succ1) {
				for (auto succ2 = vert_start->second.cbegin(); succ2 != vert_start->second.cend(); ++succ2) {					
					succ1_val = *succ1;
					succ2_val = *succ2;
					if (succ1_val != succ2_val) {						
						for (auto succ_of_succ1 = graph.find(succ1_val)->second.cbegin(); succ_of_succ1 < graph.find(succ1_val)->second.cend(); ++succ_of_succ1) {
							for (auto succ_of_succ2 = graph.find(succ2_val)->second.cbegin(); succ_of_succ2 < graph.find(succ2_val)->second.cend(); ++succ_of_succ2) {								
								int succ_of_succ1_val = *succ_of_succ1;
								int succ_of_succ2_val = *succ_of_succ2;
								if (*succ_of_succ1 == *succ_of_succ2) {
									std::cout << "not line graph |" << std::endl;	
									return false;
								}								
							}							
						}
					}
					
				}
			}
		}
		vert_start_val++;
	}
	std::cout << "line graph |" << std::endl;
	return true;
}


int adjoint(std::map <int, std::vector<int>> graph) {

	bool same = false;
	std::cout << std::endl;
	for (auto vert1 = graph.cbegin(); vert1 != std::prev(graph.cend()); ++vert1) {
		if (vert1->second.size() > 1) {
			const auto duplicate = std::adjacent_find(vert1->second.cbegin(), vert1->second.cend());
			if (duplicate != vert1->second.end()){
				std::cout << "Multigraph, multiple edge:  " << vert1->first << " -> " << *duplicate << "\n";
				return 0;
			}				
			/*for (auto succ1 = vert1->second.cbegin(); succ1 != vert1->second.cend(); ++succ1) {
				for (auto succ2 = std::next(succ1); succ2 != vert1->second.cend(); ++succ2) {
					if (*succ1 == *succ2) {
						std::cout << vert1->first;
						std::cout << ": " << "a " << *succ1 << "  b " << *succ2 << std::endl;
						std::cout << "! multi graph !" << std::endl;
						std::cout << "| !graph not-adjoint! |" << std::endl;
						return 0;
					}
				}
			}*/
		}
		for (auto vert2 = std::next(graph.cbegin()); vert2 != graph.cend(); ++vert2) {			
			if (vert1 != vert2) {
				//std::cout << std::endl;
				//std::cout << "A:" << vert1->first;
				//std::cout << " B:" << vert2->first;				
				if (vert1->second == vert2->second) {
					same = true;					
				}				
				else if (vert1->second.size() >= 1 && vert2->second.size() >= 1) {
					for (auto succ1 = vert1->second.cbegin(); succ1 != vert1->second.cend(); ++succ1) {
						for (auto succ2 = vert2->second.cbegin(); succ2 != vert2->second.cend(); ++succ2) {
							if (*succ1 == *succ2) {
								std::cout << " " << *succ1 << " == " << *succ2 << " not ok ";
								std::cout << "| !graph NOT ADJOINT! |" << std::endl;
								same = false;
								return 0;
							}
							else {
								same = true;								
								//std::cout <<  std::endl;								
								//std::cout << " " << *succ1 << " != " << *succ2;
								//std::cout << "  ok " << std::endl;
							}
						}
					}
					if (same == false) {
						std::cout << " not same ";
						std::cout << "| !graph NOT ADJOINT!  |" << std::endl;
						return 0;
					}
				}
			}
		}
	}
	if (same == true) {
		std::cout << "| adjoint graph  |";
		return 1;
	}
}


int main()
{
	std::cout << "Provide filename: " << std::endl;
	std::cin >> infile;
	read_graph_from_file(infile);
	std::cout << "graph G: " << std::endl;
	print_graph(adj_list_G);
	adj_list_to_edges(adj_list_G);
	save_dot_format(edges_G, "G");
	//print_vector_of_vector(edges_G);
	//print_curr_vertex_successors(graph_G,8);
	//print_vector_of_vector(adj_list);
	if (adjoint(adj_list_G)) {		 
			linearity(adj_list_G);
			transform(adj_list_G);	
	};	
	return 0;
}
