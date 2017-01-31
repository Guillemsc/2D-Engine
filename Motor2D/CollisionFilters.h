#ifndef _COLLISIONFILTERS__H__
#define _COLLISIONFILTERS__H__

// -----------------------------
//		Collision Control
// -----------------------------

// Category 2^x
int CATEGORY_PLAYER = 0x0001;  
int CATEGORY_SCENERY = 0x0002;

// Mask
int MASK_PLAYER = CATEGORY_SCENERY; // | ...
int MASK_SCENERY = -1;

// PhysBody enum
enum class pbody_type
{
	p_t_null,
	p_t_world
};

// Fixture enum
enum class fixture_type
{
	f_t_null,
	f_t_down_ball
};

#endif // !_COLLISIONFILTERS__H__