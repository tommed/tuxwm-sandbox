#include "opengl.h"

void show_image(XImage *img)
{
	ClutterActor *stage, *actor;
	
	// init stage
	clutter_init(0, NULL);
	stage = clutter_stage_get_default(); // XX TODO: use root window?
	
	// init actor
	actor = clutter_texture_new();
	clutter_texture_set_from_rgb_data(CLUTTER_TEXTURE(actor), img->data, False, img->width, img->height, img->bytes_per_line, 4, (ClutterTextureFlags)0, NULL);
	clutter_container_add(CLUTTER_CONTAINER(stage), actor, NULL);
  clutter_actor_set_position(actor, 10, 10);
  
  g_signal_connect(stage, "button-press-event", clutter_main_quit, NULL);
  
  // show and wait for exit
  clutter_actor_show(stage);
  clutter_main();
}
