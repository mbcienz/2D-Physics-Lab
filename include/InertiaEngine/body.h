typedef enum
{
    SHAPE_CIRCLE,
    SHAPE_BOX
} ShapeType;


// define the attributes specific for the circle shape
typedef struct 
{
    float radius;
} CircleShape;


// define the attributes specific for the circle shape
typedef struct 
{
    float width, height;
} BoxShape;


// define the shape
typedef struct 
{
    ShapeType type;
    union 
    {
        CircleShape circle;
        BoxShape    box;
    } data;  
    
} Shape;


// define the body
typedef struct
{
    Shape shape;

    double px, py;              // position
    double vx, vy;              // velocity
    double fx, fy;              // force

    double mass, inv_mass;      // mass and inverted mass

} Body;

// init the circle body
void body_init_circle(Body *b, double px, double py,  double vx, double vy, float radius, double mass);

// init the box body
void body_init_box(Body *b, double px, double py,  double vx, double vy, float width, float height, double mass);

// apply force to a body
void body_apply_force(Body *b, double fx, double fy);
