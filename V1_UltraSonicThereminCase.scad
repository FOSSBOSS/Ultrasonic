$fn = 100; // Set the resolution for the circles

// Parameters
hole_diameter = 16; // Diameter of the holes
x_spacing = 60; // Spacing between the centers of the holes on the x-axis
y_spacing = 24; // Spacing between the centers of the holes on the y-axis
wall_thickness = 2; // Thickness of the walls
length = 240; // Length of the case
width = 60; // Width of the case
thickness = 5; // Thickness of the case
side_wall_height = 15; // Height of the side wall
side_wall_thickness = 3; // Thickness of the side wall

// Create the case
module case() {
    cube([length, width, thickness], center = true);
}

// Create a single hole
module hole() {
    cylinder(h = thickness, d = hole_diameter, center = true);
}

// Create the holes grid
module holes() {
    for (i = [0:3]) {
        for (j = [0:1]) {
            translate([i * x_spacing - x_spacing/2, j * y_spacing - y_spacing/2, 0])
                hole();
        }
    }
}

// Create the side wall
module side_wall() {
    difference() {
        cube([length + 2 * side_wall_thickness, width + 2 * side_wall_thickness, side_wall_height], center = true);
        translate([0, 0, -1]) cube([length + 2 * side_wall_thickness - 2, width + 2 * side_wall_thickness - 2, side_wall_height + 2], center = true); // Add a slight margin
    }
}

// Combine the case, holes, and side wall
difference() {
    union() {
        translate([60, 0, 0]) {
            case();
            side_wall();
        }
        
    }
    holes();
}
