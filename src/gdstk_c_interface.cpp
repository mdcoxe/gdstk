#include <gdstk/gdstk_c_interface.h>
#include <gdstk/library.hpp>
#include <gdstk/cell.hpp>
#include <gdstk/polygon.hpp>
#include <gdstk/flexpath.hpp>
#include <gdstk/reference.hpp>

extern "C" {

Library_t* gdstk_read_gds(const char* filename, double unit, double tolerance, int* error_code) {
    gdstk::ErrorCode err;
    gdstk::Library* lib = new gdstk::Library(gdstk::read_gds(filename, unit, tolerance, nullptr, &err));
    if (error_code) *error_code = static_cast<int>(err);
    return reinterpret_cast<Library_t*>(lib);
}

void gdstk_library_free(Library_t* library) {
    delete reinterpret_cast<gdstk::Library*>(library);
}

const char* gdstk_library_get_name(const Library_t* library) {
    return reinterpret_cast<const gdstk::Library*>(library)->name;
}

uint64_t gdstk_library_get_cell_count(const Library_t* library) {
    return reinterpret_cast<const gdstk::Library*>(library)->cell_array.count;
}

Cell_t* gdstk_library_get_cell(const Library_t* library, uint64_t index) {
    const gdstk::Library* lib = reinterpret_cast<const gdstk::Library*>(library);
    if (index < lib->cell_array.count) {
        return reinterpret_cast<Cell_t*>(lib->cell_array[index]);
    }
    return nullptr;
}

const char* gdstk_cell_get_name(const Cell_t* cell) {
    return reinterpret_cast<const gdstk::Cell*>(cell)->name;
}

int gdstk_cell_get_polygons(const Cell_t* cell, Polygon_t** polygons, int* count) {
    const gdstk::Cell* cpp_cell = reinterpret_cast<const gdstk::Cell*>(cell);
    *count = static_cast<int>(cpp_cell->polygon_array.count);
    *polygons = reinterpret_cast<Polygon_t*>(cpp_cell->polygon_array.items);
    return 0;
}

int gdstk_cell_get_paths(const Cell_t* cell, Path_t** paths, int* count) {
    const gdstk::Cell* cpp_cell = reinterpret_cast<const gdstk::Cell*>(cell);
    *count = static_cast<int>(cpp_cell->flexpath_array.count);
    *paths = reinterpret_cast<Path_t*>(cpp_cell->flexpath_array.items);
    return 0;
}

int gdstk_cell_get_references(const Cell_t* cell, CellReference_t** references, int* count) {
    const gdstk::Cell* cpp_cell = reinterpret_cast<const gdstk::Cell*>(cell);
    *count = static_cast<int>(cpp_cell->reference_array.count);
    *references = reinterpret_cast<CellReference_t*>(cpp_cell->reference_array.items);
    return 0;
}

int gdstk_polygon_get_points(const Polygon_t* polygon, double** points, int* count) {
    const gdstk::Polygon* cpp_polygon = reinterpret_cast<const gdstk::Polygon*>(polygon);
    *count = static_cast<int>(cpp_polygon->point_array.count);
    *points = reinterpret_cast<double*>(cpp_polygon->point_array.items);
    return 0;
}

int gdstk_path_get_points(const Path_t* path, double** points, int* count) {
    const gdstk::FlexPath* cpp_path = reinterpret_cast<const gdstk::FlexPath*>(path);
    *count = static_cast<int>(cpp_path->spine.point_array.count);
    *points = reinterpret_cast<double*>(cpp_path->spine.point_array.items);
    return 0;
}

int gdstk_polygon_get_layer(const Polygon_t* polygon) {
    const gdstk::Polygon* cpp_polygon = reinterpret_cast<const gdstk::Polygon*>(polygon);
    return gdstk::get_layer(cpp_polygon->tag);
}

double gdstk_path_get_width(const Path_t* path) {
    const gdstk::FlexPath* cpp_path = reinterpret_cast<const gdstk::FlexPath*>(path);
    if (cpp_path->num_elements > 0 && cpp_path->elements[0].half_width_and_offset.count > 0) {
        return cpp_path->elements[0].half_width_and_offset[0].u * 2;
    }
    return 0.0;
}

int gdstk_path_get_layer(const Path_t* path) {
    const gdstk::FlexPath* cpp_path = reinterpret_cast<const gdstk::FlexPath*>(path);
    if (cpp_path->num_elements > 0) {
        return gdstk::get_layer(cpp_path->elements[0].tag);
    }
    return 0;
}

const char* gdstk_reference_get_cell_name(const CellReference_t* reference) {
    const gdstk::Reference* cpp_reference = reinterpret_cast<const gdstk::Reference*>(reference);
    return cpp_reference->type == gdstk::ReferenceType::Cell ? cpp_reference->cell->name : nullptr;
}

void gdstk_reference_get_position(const CellReference_t* reference, double* x, double* y) {
    const gdstk::Reference* cpp_reference = reinterpret_cast<const gdstk::Reference*>(reference);
    *x = cpp_reference->origin.x;
    *y = cpp_reference->origin.y;
}

double gdstk_reference_get_rotation(const CellReference_t* reference) {
    const gdstk::Reference* cpp_reference = reinterpret_cast<const gdstk::Reference*>(reference);
    return cpp_reference->rotation;
}

void gdstk_reference_get_magnification(const CellReference_t* reference, double* x, double* y) {
    const gdstk::Reference* cpp_reference = reinterpret_cast<const gdstk::Reference*>(reference);
    *x = cpp_reference->magnification;
    *y = cpp_reference->magnification;
}

}