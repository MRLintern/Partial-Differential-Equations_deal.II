
//program to generate 2 different types of grid/mesh using the deal.II library

//--import all required functionality from deal.II--//

//triangulation class
#include <deal.II/grid/tria.h>

//generate standard grids
#include <deal.II/grid/grid_generator.h>

//output graphics
#include <deal.II/grid/grid_out.h>

//usual required C++ libraries
#include <iostream>
#include <fstream>
#include <cmath>

//all functions and classes in deal.II namespace
using namespace dealii;

//--functions for generating the grids--//

//generate 1st mesh; unit-square domain
void first_grid() {

	//object for a triangulation 2D domain
	Triangulation<2> triangulation;

	//fill triangulation with single cell for square domain
	GridGenerator::hyper_cube(triangulation);

	//refine the triangulation 4 times to give 256 cells; 2^4 = 256
	triangulation.refine_global(4);

	//scalable vector graphics (svg) format file for imaging
	std::ofstream out("grid-1.svg");

	//instantiate GridOut object for data output
	GridOut grid_out;

	//write data to svg file for visualisation
	grid_out.write_svg(triangulation, out);

	std::cout<<"Grid written to grid-1.svg"<<"\n";

}

//2nd mesh will be a ring domain
void second_grid() {

	////object for a triangulation 2D domain
	Triangulation<2> triangulation;

	//center of the ring
	const Point<2> center(1,0);

	//radii for inner and outer circle
	const double inner_radius{0.5}, outer_radius{1.0};

	//attaches a spherical manifold to all cells.
	//causes cells to be refined with calculations in spherical coordinates
	GridGenerator::hyper_shell(triangulation, center, inner_radius, outer_radius, 10);

	//refine the grid in 5 steps towards the inner circle of the domain
	for (unsigned int step{}; step < 5; ++step) {

		//iterate over all active cells
		for (auto& cell : triangulation.active_cell_iterators()) {

			//loop over vertices of the cells
			for (const auto v : cell -> vertex_indices()) {

				const double distance_from_center {center.distance(cell -> vertex(v));

				if (std::fabs(distance_from_center - inner_radius) <= 1e-6 * inner_radius) {

					cell -> set_refine_flag();
					break;
				}

			}
		}

		//all cells have been refined so the triangulation performs the refinement
		triangulation.execute_coarsening_and_refinement();
	}

	//--refinement done; write the meshes to files--//

	std::ofstream out("grid-2.svg");

	GridOut grid_out;

	grid_out.write_svg(triangulation, out);

	std::cout<<"Grid written to grid-2.svg"<<"\n";

}

//call functions to make the meshes
int main() {

	first_grid();
	second_grid();

}

