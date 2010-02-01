/*
 * dice.c: Draws a simple dice using Cairo and GTK+ which is rolled by
 *         pressing ENTER or pressing a mouse button. Exit with 'q'.
 *
 * Copyright 2009 (c) Gaute Hope <eg@gaute.vetsj.com>
 *
 * Distributed under the GNU General Public Licence v3
 */


# include <math.h>
# include <gtk/gtk.h>
# include <gdk/gdkkeysyms.h>
# include <cairo.h>

# define START_T 25     // Top margin
# define START_1 25     // Left margin

GtkWidget *window;
int       one, two;

void      roll ();
static    gboolean on_expose_event (GtkWidget*, GdkEventExpose*, gpointer);
void      draw_dice (cairo_t *cr, int dice, int START, int WIDTH,
                     int HEIGHT);

static gboolean on_key_press (GtkWidget *widget,
                              GdkEventKey *event,
                              gpointer data) {
  if (event->type == GDK_KEY_PRESS) {
    if ((event->keyval == GDK_Return) || (event->keyval == GDK_r)) {
      roll ();
      gtk_widget_queue_draw (widget);
      return FALSE;
    } else if (event->keyval == GDK_q) {
      gtk_main_quit ();
      return TRUE;
    }
  }
  if (event->type == GDK_BUTTON_PRESS) {
    roll ();
    gtk_widget_queue_draw (widget);
    return FALSE;
  }
}

static gboolean size_changed (GtkWidget *widget, GdkEventAny *event, gpointer data) {
  gtk_widget_queue_draw (widget);
  return FALSE;
}


void draw_dice (cairo_t *cr, int dice, int START, int WIDTH, int HEIGHT) {
  switch (dice) {
    default:
    case 1:
      cairo_arc (cr, START + WIDTH / 2, START_T + HEIGHT / 2, 40, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      break;
    case 2:
      cairo_arc (cr, START + WIDTH / 4, START_T + HEIGHT / 2, 20, 0, 2*M_PI);
      cairo_arc (cr, START + WIDTH / 4 + WIDTH / 2, START_T + HEIGHT / 2, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      break;
    case 3:
      cairo_arc (cr, START + WIDTH / 4, START_T + HEIGHT - HEIGHT / 4, 20, 0, 2*M_PI);

      cairo_arc (cr, START + WIDTH/4 + WIDTH/2, START_T + HEIGHT - HEIGHT / 4, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      cairo_arc (cr, START + WIDTH / 2, START_T + HEIGHT /4, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      break;
    case 4:
      cairo_arc (cr, START + WIDTH / 4, START_T + HEIGHT - HEIGHT / 4, 20, 0, 2*M_PI);

      cairo_arc (cr, START + WIDTH/4 + WIDTH/2, START_T + HEIGHT - HEIGHT / 4, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      cairo_arc (cr, START + WIDTH / 4, START_T + HEIGHT / 4, 20, 0, 2*M_PI);

      cairo_arc (cr, START + WIDTH/4 + WIDTH/2, START_T + HEIGHT/ 4, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      break;
    case 5:
      cairo_arc (cr, START + WIDTH / 4, START_T + HEIGHT - HEIGHT / 6, 20, 0, 2*M_PI);

      cairo_arc (cr, START + WIDTH/4 + WIDTH/2, START_T + HEIGHT - HEIGHT / 6, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      cairo_arc (cr, START + WIDTH / 4, START_T + HEIGHT / 6, 20, 0, 2*M_PI);

      cairo_arc (cr, START + WIDTH/4 + WIDTH/2, START_T + HEIGHT/ 6, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      cairo_arc (cr, START + WIDTH / 2, START_T + HEIGHT / 2, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      break;
    case 6:
      cairo_arc (cr, START + WIDTH / 4, START_T + HEIGHT - HEIGHT / 6, 20, 0, 2*M_PI);

      cairo_arc (cr, START + WIDTH/4 + WIDTH/2, START_T + HEIGHT - HEIGHT / 6, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      cairo_arc (cr, START + WIDTH / 4, START_T + HEIGHT / 6, 20, 0, 2*M_PI);

      cairo_arc (cr, START + WIDTH/4 + WIDTH/2, START_T + HEIGHT/ 6, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);
      cairo_arc (cr, START + WIDTH / 4, START_T + HEIGHT / 2, 20, 0, 2*M_PI);

      cairo_arc (cr, START + WIDTH/4 + WIDTH/2, START_T + HEIGHT/ 2, 20, 0, 2*M_PI);
      cairo_stroke_preserve (cr);
      cairo_fill (cr);

      break;
  }
}

static gboolean on_expose_event (GtkWidget *widget,
                                 GdkEventExpose *event,
                                 gpointer data) {
  int START_2, HEIGHT, WIDTH;
  int w, h;
  gtk_window_get_size (GTK_WINDOW (widget), &w, &h);

  HEIGHT = h - (START_1*2);
  WIDTH = (w - (START_1*3)) / 2;
  START_2 = START_1*2 + WIDTH;

  cairo_t *cr;
  cr = gdk_cairo_create (widget->window);

  cairo_set_line_width (cr, 9);

  cairo_set_source_rgb (cr, 0.69, 0.19, 0);
  cairo_rectangle (cr, START_1, START_T, WIDTH , HEIGHT);
  cairo_rectangle (cr, START_2, START_T, WIDTH, HEIGHT);
  cairo_stroke_preserve (cr);
  cairo_set_source_rgb (cr, 0.3, 0.4, 0.6);
  cairo_fill (cr);

  cairo_set_source_rgb (cr, 1, 1, 1);

  draw_dice (cr, one, START_1, WIDTH, HEIGHT);
  draw_dice (cr, two, START_2, WIDTH, HEIGHT);

  cairo_destroy (cr);
  return FALSE;
}

void roll () {
  one = (random () % 6) + 1;
  two = (random () % 6) + 1;
}

int main (int argc, char **argv) {
  gtk_init (&argc, &argv);

  roll ();

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  g_signal_connect (G_OBJECT (window), "expose-event", G_CALLBACK (on_expose_event), NULL);
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT (window), "key-press-event", G_CALLBACK (on_key_press), NULL);
  g_signal_connect (G_OBJECT (window), "button-press-event", G_CALLBACK (on_key_press), NULL);
  g_signal_connect (G_OBJECT (window), "size-allocate", G_CALLBACK (size_changed), NULL);


  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW(window), 825, 425);
  /* gtk_window_set_resizable (GTK_WINDOW (window), FALSE); */ // Why doesn't this work?
  gtk_window_resize (GTK_WINDOW (window), 825, 425);
  gtk_widget_set_app_paintable (window, TRUE);
  gtk_widget_set_events (window, GDK_ALL_EVENTS_MASK);

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}

