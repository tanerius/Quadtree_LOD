### Quadtree LOD - Rendering planets and surfaces

**Summary** 
Implementation of a Quadtree LOD in terrain rendering (such as planets). The representation of the planet is with an ellipsoid. Im hoping this will result in either a complete planet rendering engine or something that will help me in my upcoming project with the Unreal Engine 4.

**Coordinate Systems**
The coordinate systems used are :

* Geographic coordinates - Tuple(lng, lat, height)
* Cartesian coordinate system - for addressing the viewports and screen stuff

**Spheres and allipses**
These are some stuff that are important to point out.

A point anywhere on a sphere:
x^2 + y^2 + z^2 = r^2

A point on a spheres surface:
xs^2 + ys^2 + zs^2 = r^2

A point on an ellipse surface:
(xs^2)/(a^2) + (ys^2)/(b^2) + (zs^2)/(c^2) = 1
(where a,b and c are radii on the x, y and z axis)

Ellipses have two types of surface normals:
* Geocentric - a normalized vector from the center point 
* Geodetic - a vector normal to a tangent of a point on the actual surface of the ellipse 

For Earth: 
a == b == 6,378,137m (semimajor axis)
c == 6,356,752.3142m (semiminor axis)

