#include <glib.h>

#include <gdk/gdkx.h>
#include <epoxy/glx.h>
#include <epoxy/gl.h>
#include <gtk/gtk.h>

#include "Logger.h"
#include "OpenGLApplication.h"

//fool compile into thinking a variable is using. prevents warnings
#define IGNORE_VAR(type, identifier)            \
  {                                             \
    type IGNORED_VARIABLE_abcd = identifier;    \
    identifier = IGNORED_VARIABLE_abcd;         \
  }

OpenGLApplication *app;
log4cpp::Category* logger = Logger::GetLogger();
GtkWidget *window;
GtkEventBox *evtBxGLArea;
GtkBuilder *builder;
GtkRevealer *rvlEye, *rvlLookAt, *rvlUp;
GtkScale *sclEyeX, *sclEyeY, *sclEyeZ, *sclLookAtX, *sclLookAtY, *sclLookAtZ, *sclUpX, *sclUpY, *sclUpZ;

static void on_window_closed (GtkWidget *widget, gpointer data)
{
  gtk_main_quit ();
}

static void onScl (GtkRange *range, gpointer  user_data) {
  double eyeX = gtk_range_get_value((GtkRange*)sclEyeX);
  double eyeY = gtk_range_get_value((GtkRange*)sclEyeY);
  double eyeZ = gtk_range_get_value((GtkRange*)sclEyeZ);

  double lookAtX = gtk_range_get_value((GtkRange*)sclLookAtX);
  double lookAtY = gtk_range_get_value((GtkRange*)sclLookAtY);
  double lookAtZ = gtk_range_get_value((GtkRange*)sclLookAtZ);

  double upX = gtk_range_get_value((GtkRange*)sclUpX);
  double upY = gtk_range_get_value((GtkRange*)sclUpY);
  double upZ = gtk_range_get_value((GtkRange*)sclUpZ);

  glm::vec3 eye = glm::vec3(eyeX,eyeY,eyeZ);
  glm::vec3 lookAt = glm::vec3(lookAtX,lookAtY,lookAtZ);
  glm::vec3 up = glm::vec3(upX,upY,upZ);

  app->UpdateCamera(eye,lookAt,up);
}

static void onRvlEye (GtkWidget *w, gpointer d)
{
  gboolean revealed = gtk_revealer_get_child_revealed (rvlEye);
  gtk_revealer_set_reveal_child (rvlEye, !revealed);
}

static void onRvlLookAt (GtkWidget *w, gpointer d)
{
  gboolean revealed = gtk_revealer_get_child_revealed (rvlLookAt);
  gtk_revealer_set_reveal_child (rvlLookAt, !revealed);
}

static void onRvlUp (GtkWidget *w, gpointer d)
{
  gboolean revealed = gtk_revealer_get_child_revealed (rvlUp);
  gtk_revealer_set_reveal_child (rvlUp, !revealed);
}

static gboolean key_release_event(GtkGLArea *widget,
                                  GdkEvent  *event,
                                  gpointer   user_data) {

  //std::stringstream sstm;
  //sstm.str(std::string());
  //sstm << "Key pressed " << ((GdkEventKey*)event)->keyval << std::endl;
  //logger->info(sstm.str());

  app->OnKeyReleased(((GdkEventKey*)event)->keyval);

  gtk_widget_queue_draw((GtkWidget*)widget);

  return true;
}

static void scroll_event(GtkWidget *widget,
                         GdkEvent  *event,
                         gpointer   user_data) {
  logger->info("got scroll.");
  //printf("got scroll.");
  app->OnScroll(((GdkEventScroll*)event)->direction);

  gtk_widget_queue_draw((GtkWidget*)widget);
}

static void motion_notify_event(GtkWidget *widget,
                                GdkEvent  *event,
                                gpointer   user_data) {
  //logger->info("got motion.");
  //printf("got scroll.");
  //app->OnScroll(((GdkEventScroll*)event)->direction);

  //gtk_widget_queue_draw((GtkWidget*)widget);

  GdkEventMotion *evtMotion = (GdkEventMotion*)event;

  //std::stringstream sstm;
  //sstm.str(std::string());
  //sstm << "State " << evtMotion->state << " " << GDK_BUTTON1_MASK << " " << (evtMotion->state & GDK_BUTTON1_MASK) << std::endl;
  //logger->info(sstm.str());

  if (((evtMotion->state) & GDK_BUTTON1_MASK)> 1) {
    logger->info("got motion.");
    app->OnDrag(evtMotion->x,evtMotion->y);
    gtk_widget_queue_draw((GtkWidget*)widget);
  }
}

static void button_press_event(GtkGLArea *widget,
                               GdkEvent  *event,
                               gpointer   user_data) {

  //logger->info("c pressed");
  GdkEventButton* evtBtn = (GdkEventButton*)event;
  //std::cout << "btn x: "<<evtBtn->x <<", y: " << evtBtn->y << std::endl;
  app->OnButtonPressed(evtBtn->button, evtBtn->x, evtBtn->y);

  gtk_widget_queue_draw((GtkWidget*)widget);
}

static void button_release_event(GtkGLArea  *widget,
                                 GdkEvent  *event,
                                 gpointer   user_data) {

  //logger->info("c released");
  GdkEventButton* evtBtn = (GdkEventButton*)event;
  app->OnButtonReleased(evtBtn->button, evtBtn->x, evtBtn->y);

  gtk_widget_queue_draw((GtkWidget*)widget);
}


/*static GdkGLContext* create_context (GtkGLArea *area,
  gpointer   user_data) {

  }*/

static void resize (GtkGLArea *area,
                    gint       width,
                    gint       height,
                    gpointer   user_data) {

  printf("Resize width: %d, height: %d\n",width,height);
}

static gboolean render(GtkGLArea *area, GdkGLContext *context)
{
  IGNORE_VAR(GdkGLContext*, context);
  IGNORE_VAR(GtkGLArea*, area);

  app->Render();

  return true;
}

static gboolean realize(GtkGLArea *area, GdkGLContext *context)
{
  IGNORE_VAR(GdkGLContext*, context);

  gtk_gl_area_make_current(GTK_GL_AREA(area));
  if (gtk_gl_area_get_error (GTK_GL_AREA(area)) != NULL)
  {
    printf("Failed to initialiize buffers\n");
    return FALSE;
  }

  int width, minWidth, natWidth;
  int height, minHeight, natHeight;
  gtk_widget_get_preferred_width((GtkWidget*)area,&minWidth,&natWidth);
  gtk_widget_get_preferred_height((GtkWidget*)area,&minHeight,&natHeight);
  width = gtk_widget_get_allocated_width((GtkWidget*)area);
  height = gtk_widget_get_allocated_height((GtkWidget*)area);

  printf("Starting OpenGLApplication Width=%d, MinWidth=%d, NatWidth=%d, Height=%d, MinHeight=%d, NatHeight=%d\n",width,minWidth,natWidth,height,minHeight,natHeight);
  app = new OpenGLApplication(width,height);
  app->Init();

  return true;
}

static void unrealize (GtkWidget *widget,
                       gpointer   user_data) {
  app->Shutdown();
  delete app;
}


static void connection_mapper (GtkBuilder *builder, GObject *object,
                               const gchar *signal_name, const gchar *handler_name,
                               GObject *connect_object, GConnectFlags flags, gpointer user_data)
{
  g_print ("Verbinde %s mit %s\n", signal_name, handler_name);

  if (g_strcmp0(handler_name, "gtk_main_quit")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(on_window_closed),0);
    //} else if (g_strcmp0(handler_name, "create_context")==0) {
    //g_signal_connect(object,signal_name,G_CALLBACK(create_context),user_data);
  } else if (g_strcmp0(handler_name, "render")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(render),0);
  } else if (g_strcmp0(handler_name, "resize")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(resize),user_data);
  } else if (g_strcmp0(handler_name, "realize")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(realize),0);
  } else if (g_strcmp0(handler_name, "unrealize")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(unrealize),user_data);
  } else if (g_strcmp0(handler_name, "key_release_event")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(key_release_event),user_data);
  } else if (g_strcmp0(handler_name, "scroll_event")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(scroll_event),user_data);
  } else if (g_strcmp0(handler_name, "motion_notify_event")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(motion_notify_event),user_data);
  } else if (g_strcmp0(handler_name, "button_press_event")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(button_press_event),user_data);
  } else if (g_strcmp0(handler_name, "button_release_event")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(button_release_event),user_data);
  } else if (g_strcmp0(handler_name, "onRvlEye")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(onRvlEye),user_data);
  } else if (g_strcmp0(handler_name, "onRvlLookAt")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(onRvlLookAt),user_data);
  } else if (g_strcmp0(handler_name, "onRvlUp")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(onRvlUp),user_data);
  } else if (g_strcmp0(handler_name, "onScl")==0) {
    g_signal_connect(object,signal_name,G_CALLBACK(onScl),user_data);
  } else {
    g_print ("unbekannte Callback %s %s\n",handler_name, signal_name);
  }
}

static void InitWindow() {
  window = GTK_WIDGET(gtk_builder_get_object (builder, "CubeVisor"));
}

static void InitGL() {
  evtBxGLArea = (GtkEventBox *)gtk_builder_get_object(builder,"evtBxGLArea");
}

static void InitScales() {
  sclEyeX = (GtkScale *)gtk_builder_get_object(builder,"sclEyeX");
  sclEyeY = (GtkScale *)gtk_builder_get_object(builder,"sclEyeY");
  sclEyeZ = (GtkScale *)gtk_builder_get_object(builder,"sclEyeZ");

  sclLookAtX = (GtkScale *)gtk_builder_get_object(builder,"sclLookAtX");
  sclLookAtY = (GtkScale *)gtk_builder_get_object(builder,"sclLookAtY");
  sclLookAtZ = (GtkScale *)gtk_builder_get_object(builder,"sclLookAtZ");

  sclUpX = (GtkScale *)gtk_builder_get_object(builder,"sclUpX");
  sclUpY = (GtkScale *)gtk_builder_get_object(builder,"sclUpY");
  sclUpZ = (GtkScale *)gtk_builder_get_object(builder,"sclUpZ");
}

static void InitRevealers() {
  rvlEye = (GtkRevealer *)gtk_builder_get_object (builder, "rvlEye");
  rvlLookAt = (GtkRevealer *)gtk_builder_get_object (builder, "rvlLookAt");
  rvlUp = (GtkRevealer *)gtk_builder_get_object (builder, "rvlUp");
}

static void InitWidgets() {
  InitWindow();
  InitGL();
  InitScales();
  InitRevealers();
}

int main (int argc, char *argv[])
{

  GError *errors = NULL;


  gtk_init (&argc, &argv);
  builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "interface.ui.xml", &errors);
  //gtk_builder_connect_signals (builder, builder);
  gtk_builder_connect_signals_full (builder, connection_mapper, NULL);
  InitWidgets();
  gtk_widget_add_events(GTK_WIDGET(evtBxGLArea), GDK_SCROLL_MASK);
  gtk_widget_add_events(GTK_WIDGET(window), GDK_SCROLL_MASK);
  gtk_widget_show_all (window);
  gtk_main ();
  return 0;
}
