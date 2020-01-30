#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>


int main() {
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	//ball starting position
	float ball_x = 20;
	float ball_y = 200;

	//ball speed
	float ball_dx = -5.0, ball_dy = 4.0;

	//controls redner section
	bool redraw = true;

	al_init();
	al_init_primitives_addon();

	timer = al_create_timer(1.0 / 60);


	display = al_create_display(500, 500);

	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//TIMER SECTION (handles physics)
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (ball_x < 0 || ball_x > 500) { //bounces against side walls
				ball_dx = -ball_dx;
			}

			if (ball_y < 0 || ball_y > 500) { //bounce against top and bottom walls
				ball_dy = -ball_dy;
			}

			//MOVE
			ball_x += ball_dx;
			ball_y += ball_dy;

			redraw = true;
		}
		//lets you close with the x button
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		//RENDER SECTION
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0)); //clears the screen

			al_draw_filled_circle(ball_x, ball_y, 20, al_map_rgb(200, 200, 100));

			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
