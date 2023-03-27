
//program to generate 2 different types of grid/mesh using the deal.II library

//import all required functionality from deal.II
#include <deal.II/grid/tria.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_out.h>

//usual C++ stuff
#include <iostream>
#include <fstream>
#include <cmath>

using namespace dealii;

//--functions for generating the grids--//

void first_grid() {

	Triangulation<2> triangulation;

	GridGenerator::hyper_cube(triangulation);

	std::ofstream out("grid-1.svg");

	GridOut grid_out;

	grid_out.write_svg(triangulation, out);

	std::cout<<"Grid written to grid-1.svg"<<"\n";

}

void second_grid() {

	Triangulation<2> triangulation;

	const Point<2> center(1,0);
	const double inner_radius{0.5}, outer_radius{1.0};

	GridGenerator::hyper_shell(triangulation, center, inner_radius, outer_radius, 10);

	for (unsigned int step{}; step < 5; ++step) {

		for (auto& cell : triangulation.active_cell_iterators()) {

			for (const auto v : cell -> vertex_indices()) {

				const double distance_from_center {center.distance(cell -> vertex(v));

				if (std::fabs(distance_from_center - inner_radius) <= 1e-6 * inner_radius) {

					cell -> set_refine_flag();
					break;
				}

			}
		}

		triangulation.execute_coarsening_and_refinement();
	}

	std::ofstream out("grid-2.svg");

	GridOut grid_out;

	grid_out.write_svg(triangulation, out);

	std::cout<<"Grid written to grid-2.svg"<<"\n";

}

int main() {

	//call functions to make the grids

	first_grid();
	second_grid();
	
}

