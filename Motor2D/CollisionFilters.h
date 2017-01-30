#ifndef _COLLISIONFILTERS__H__
#define _COLLISIONFILTERS__H__

//2^x

// Category
int CATEGORY_PLAYER = 0x0001;  
int CATEGORY_SCENERY = 0x0002;

// Mask
int MASK_PLAYER = CATEGORY_SCENERY;
int MASK_SCENERY = -1;

// PhysBody enum
enum class pbody_type
{
	pbody_type_null,
	pbody_type_world
};

// Fixture enum
enum class fixture_type
{
	fixuture_type_null,
	fixuture_type_down_ball
};

#endif // !_COLLISIONFILTERS__H__