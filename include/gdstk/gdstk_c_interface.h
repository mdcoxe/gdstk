#ifndef GDSTK_C_INTERFACE_H
#define GDSTK_C_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Opaque types
typedef struct Library_t Library_t;
typedef struct Cell_t Cell_t;
typedef struct Polygon_t Polygon_t;
typedef struct Path_t Path_t;
typedef struct CellReference_t CellReference_t;

// Function declarations
Library_t* gdstk_read_gds(const char* filename, double unit, double tolerance, int* error_code);
void gdstk_library_free(Library_t* library);
const char* gdstk_library_get_name(const Library_t* library);
uint64_t gdstk_library_get_cell_count(const Library_t* library);
Cell_t* gdstk_library_get_cell(const Library_t* library, uint64_t index);
const char* gdstk_cell_get_name(const Cell_t* cell);

int gdstk_cell_get_polygons(const Cell_t* cell, Polygon_t** polygons, int* count);
int gdstk_cell_get_paths(const Cell_t* cell, Path_t** paths, int* count);
int gdstk_cell_get_references(const Cell_t* cell, CellReference_t** references, int* count);

int gdstk_polygon_get_points(const Polygon_t* polygon, double** points, int* count);
int gdstk_polygon_get_layer(const Polygon_t* polygon);

int gdstk_path_get_points(const Path_t* path, double** points, int* count);
double gdstk_path_get_width(const Path_t* path);
int gdstk_path_get_layer(const Path_t* path);

const char* gdstk_reference_get_cell_name(const CellReference_t* reference);
void gdstk_reference_get_position(const CellReference_t* reference, double* x, double* y);
double gdstk_reference_get_rotation(const CellReference_t* reference);
void gdstk_reference_get_magnification(const CellReference_t* reference, double* x, double* y);

#ifdef __cplusplus
}
#endif

#endif // GDSTK_C_INTERFACE_H