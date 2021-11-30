
extern "C"
{
#include <igraph/igraph.h>
}
#include <vector>
#include <iostream>

int main(int argc, char **argv)
{
  std::cout << "Running" << std::endl;
  igraph_set_attribute_table(&igraph_cattribute_table);

  for (int i = 0; i < 1000; ++i)
  {

    igraph_t graph;

    igraph_rng_seed(igraph_rng_default(), 42);

    igraph_erdos_renyi_game(&graph, IGRAPH_ERDOS_RENYI_GNM, 2500, 3000,
                            IGRAPH_UNDIRECTED, IGRAPH_LOOPS_TWICE);
    igraph_cattribute_VAN_set(&graph, "id", 1, i);

    // add loops to have igraph_simplify simplify something
    igraph_add_edge(&graph, 1, 1);
    igraph_add_edge(&graph, 1, 2);
    igraph_add_edge(&graph, 2, 1);

    igraph_attribute_combination_t comb;
    igraph_attribute_combination_init(&comb);
    igraph_simplify(&graph, /*multiple=*/1, /*loops=*/1, &comb);
    igraph_attribute_combination_destroy(&comb);

    igraph_vector_ptr_t components;
    igraph_vector_ptr_init(&components, 3);
    if (igraph_decompose(&graph, &components, IGRAPH_STRONG, -1, 0))
    {
      throw std::runtime_error("Failed to decompose graph.");
    }

    size_t NComponents = igraph_vector_ptr_size(&components);
    igraph_decompose_destroy(&components);

    std::cout << "Got " << NComponents << " components in random graph of " << igraph_vcount(&graph) << " vertices" << std::endl;

    igraph_destroy(&graph);
  }
}
