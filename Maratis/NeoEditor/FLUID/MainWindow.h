// generated by Fast Light User Interface Designer (fluid) version 1.0302

#ifndef MainWindow_h
#define MainWindow_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
extern void new_project_callback(Fl_Menu_*, void*);
extern void new_level_callback(Fl_Menu_*, void*);
extern void open_project_callback(Fl_Menu_*, void*);
extern void open_level_callback(Fl_Menu_*, void*);
extern void import_mesh_callback(Fl_Menu_*, void*);
extern void save_level_callback(Fl_Menu_*, long);
extern void quit_callback(Fl_Menu_*, void*);
extern void undo_callback(Fl_Menu_*, void*);
extern void redo_callback(Fl_Menu_*, void*);
extern void select_all_callback(Fl_Menu_*, void*);
extern void duplicate_object_callback(Fl_Menu_*, void*);
extern void delete_object_callback(Fl_Menu_*, void*);
extern void scene_setup_callback(Fl_Menu_*, void*);
extern void delete_scene_callback(Fl_Menu_*, void*);
extern void play_game_callback(Fl_Menu_*, void*);
extern void update_player_callback(Fl_Menu_*, void*);
extern void publish_callback(Fl_Menu_*, void*);
extern void add_mesh_callback(Fl_Menu_*, void*);
extern void add_light_callback(Fl_Menu_*, void*);
extern void add_text_callback(Fl_Menu_*, void*);
extern void add_camera_callback(Fl_Menu_*, void*);
extern void add_sound_callback(Fl_Menu_*, void*);
extern void add_scene_callback(Fl_Menu_*, void*);
extern void add_group_callback(Fl_Menu_*, void*);
extern void about_menu_callback(Fl_Menu_*, void*);
#include "GLBox.h"
#include <FL/Fl_Tree.H>
extern void scene_tree_callback(Fl_Tree*, void*);
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
extern void set_edit_type(Fl_Round_Button*, long);
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>
extern void rotation_speed_callback(Fl_Value_Input*, void*);
extern void translation_speed_callback(Fl_Value_Input*, void*);
#include <FL/Fl_Check_Button.H>
extern void ortho_callback(Fl_Check_Button*, void*);
extern void change_vue_callback(Fl_Menu_*, long);
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Input.H>
extern void edit_name_callback(Fl_Input*, void*);
extern void edit_object_callback(Fl_Value_Input*, long);
extern void edit_light_properties(Fl_Value_Input*, void*);
#include <FL/Fl_Button.H>
extern void choose_light_color(Fl_Button*, void*);
extern void edit_light_properties_chk_btn(Fl_Check_Button*, void*);
#include <FL/Fl_Clock.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Output.H>
extern void edit_object_chk_btn(Fl_Check_Button*, void*);
extern void edit_materials_callback(Fl_Button*, void*);
extern void edit_shape_callback(Fl_Menu_*, long);
extern void edit_object_properties(Fl_Value_Input*, void*);
extern void edit_camera_properties(Fl_Value_Input*, void*);
extern void choose_camera_color(Fl_Button*, void*);
extern void edit_camera_properties_chk_btn(Fl_Check_Button*, void*);
#include <FL/Fl_Text_Editor.H>
extern void edit_text_properties(Fl_Text_Editor*, void*);
extern void edit_text_properties(Fl_Input*, void*);
extern void text_find_font_callback(Fl_Button*, void*);
extern void edit_text_properties(Fl_Value_Input*, void*);
extern void text_alignment_callback(Fl_Menu_*, long);
extern void choose_text_color(Fl_Button*, void*);
extern void edit_sound_chk_btn(Fl_Check_Button*, void*);
extern void edit_sound_callback(Fl_Value_Input*, void*);
extern void new_scene_ok_callback(Fl_Button*, void*);
extern void new_scene_cancel_callback(Fl_Button*, void*);

class EditorWindow {
public:
  Fl_Double_Window* show_window();
  Fl_Menu_Bar *menu_bar;
  static Fl_Menu_Item menu_menu_bar[];
  static Fl_Menu_Item *behavior_menu;
  GLBox *glbox;
  Fl_Tree *scene_tree;
  Fl_Group *edit_group;
  Fl_Choice *scenes_menu;
  Fl_Group *speed_group;
  Fl_Value_Input *rotation_speed;
  Fl_Value_Input *translation_speed;
  Fl_Check_Button *vue_ortho_button;
  static Fl_Menu_Item menu_View[];
  Fl_Input *name_edit;
  Fl_Value_Input *xpos_edit;
  Fl_Value_Input *ypos_edit;
  Fl_Value_Input *zpos_edit;
  Fl_Value_Input *xrot_edit;
  Fl_Value_Input *yrot_edit;
  Fl_Value_Input *zrot_edit;
  Fl_Value_Input *xscale_edit;
  Fl_Value_Input *yscale_edit;
  Fl_Value_Input *zscale_edit;
  Fl_Input *parent_edit;
  Fl_Tabs *special_tab;
  Fl_Scroll *behaviors_scroll;
  Fl_Double_Window* create_light_window();
  Fl_Double_Window *light_window_object;
  Fl_Value_Input *light_radius_edit;
  Fl_Value_Input *light_color_r;
  Fl_Value_Input *light_color_g;
  Fl_Value_Input *light_color_b;
  Fl_Value_Input *light_intensity_edit;
  Fl_Check_Button *light_spot_button;
  Fl_Value_Input *spot_angle_edit;
  Fl_Value_Input *light_spot_exponent;
  Fl_Check_Button *light_shadows_button;
  Fl_Value_Input *light_shadow_bias_edit;
  Fl_Value_Input *light_shadow_blur_edit;
  Fl_Value_Input *light_shadow_quality_edit;
  Fl_Double_Window* create_publish_window();
  Fl_Double_Window* create_object_window();
  Fl_Double_Window *object_embedded_window;
  Fl_Output *object_mesh_edit;
  Fl_Check_Button *object_invisible_button;
  Fl_Check_Button *object_shadow_button;
  Fl_Choice *object_shape_choice;
  static Fl_Menu_Item menu_object_shape_choice[];
  Fl_Check_Button *object_ghost_button;
  Fl_Value_Input *object_mass_edit;
  Fl_Value_Input *object_fric_edit;
  Fl_Value_Input *object_rest_edit;
  Fl_Check_Button *object_physics_button;
  Fl_Value_Input *xpivot_edit;
  Fl_Value_Input *ypivot_edit;
  Fl_Value_Input *zpivot_edit;
  Fl_Value_Input *object_linear_damping_edit;
  Fl_Value_Input *object_angular_damping_edit;
  Fl_Value_Input *xlinear_edit;
  Fl_Value_Input *ylinear_edit;
  Fl_Value_Input *zlinear_edit;
  Fl_Value_Input *object_angular_factor_edit;
  Fl_Double_Window* create_camera_window();
  Fl_Value_Input *camera_color_r;
  Fl_Value_Input *camera_color_g;
  Fl_Value_Input *camera_color_b;
  Fl_Check_Button *camera_ortho_button;
  Fl_Value_Input *camera_fov_edit;
  Fl_Value_Input *camera_clipping_near_edit;
  Fl_Value_Input *camera_clipping_far_edit;
  Fl_Check_Button *camera_fog_button;
  Fl_Value_Input *camera_fog_distance_edit;
  Fl_Double_Window* create_text_window();
  Fl_Text_Editor *text_text_edit;
  Fl_Input *text_font_edit;
  Fl_Value_Input *text_size_edit;
  Fl_Choice *text_alignment_chooser;
  static Fl_Menu_Item menu_text_alignment_chooser[];
  Fl_Value_Input *text_r;
  Fl_Value_Input *text_g;
  Fl_Value_Input *text_b;
  Fl_Value_Input *text_a;
  Fl_Double_Window* create_sound_window();
  Fl_Output *sound_file_edit;
  Fl_Check_Button *sound_loop_button;
  Fl_Value_Input *sound_pitch_edit;
  Fl_Value_Input *sound_gain_edit;
  Fl_Value_Input *sound_radius_edit;
  Fl_Value_Input *sound_rolloff_edit;
  Fl_Check_Button *sound_relative_button;
  /**
     Scene name to use when creating a new scene
  */
  std::string scene_name; 
  Fl_Double_Window* create_scene_window();
  Fl_Input *scene_name_input;
};

class SceneSetupDlg {
public:
  static void ok_button_callback(Fl_Button* button, SceneSetupDlg* dlg);
  static void cancel_button_callback(Fl_Button* button, void*);
  static void find_file_callback(Fl_Button* button, void*);
  Fl_Double_Window* create_window();
  Fl_Input *scene_name_edit;
  Fl_Input *lua_script_edit;
  Fl_Value_Input *color_r;
  Fl_Value_Input *color_g;
  Fl_Value_Input *color_b;
  static void choose_light_color(Fl_Button* button, SceneSetupDlg* dlg);
  bool success; 
};
#include <FL/Fl_Text_Display.H>

class PlayerConsole {
public:
  Fl_Double_Window* create_window();
  Fl_Text_Display *output_edit;
  static void window_close_callback(Fl_Window* window, PlayerConsole* dlg);
  bool closed; 
  PlayerConsole();
};

class MaterialEditDlg {
  char object_name[256]; 
public:
  Fl_Double_Window* create_window(const char* name);
  Fl_Double_Window *window;
  Fl_Choice *materials_chooser;
  Fl_Value_Input *color_r;
  Fl_Value_Input *color_g;
  Fl_Value_Input *color_b;
  Fl_Value_Input *shininess_edit;
  Fl_Value_Input *opacity_edit;
  Fl_Value_Input *diffuse_r;
  Fl_Value_Input *diffuse_g;
  Fl_Value_Input *diffuse_b;
  Fl_Value_Input *specular_r;
  Fl_Value_Input *specular_g;
  Fl_Value_Input *specular_b;
  static void close_callback(Fl_Button* button, MaterialEditDlg* dlg);
  static void material_changed(Fl_Choice* choice, MaterialEditDlg* dlg);
  static void close_window_callback(Fl_Window* window, MaterialEditDlg* dlg);
  static void apply_callback(Fl_Button*, MaterialEditDlg* dlg);
  static void save_callback(Fl_Button*, MaterialEditDlg* dlg);
  static void choose_diffuse_color(Fl_Button* button, MaterialEditDlg* dlg);
  static void choose_specular_color(Fl_Button* button, MaterialEditDlg* dlg);
  static void choose_emit_color(Fl_Button* button, MaterialEditDlg* dlg);
};

class AboutDlg {
public:
  Fl_Double_Window* create_window();
  Fl_Box *editor_version_edit;
};

class PublishDlg {
  Fl_Window* window; 
public:
  Fl_Double_Window* create_window();
  Fl_Input *output_edit;
  Fl_Input *level_edit;
  static void publish_click(Fl_Button*, PublishDlg* dlg);
  static void cancel_click(Fl_Button*, PublishDlg* dlg);
  static void find_output_dir(Fl_Button*, PublishDlg* dlg);
  static void find_main_level(Fl_Button*, PublishDlg* dlg);
};
void new_scene_ok_callback(Fl_Button* button,void*);
void new_scene_cancel_callback(Fl_Button* button,void*);
#endif
