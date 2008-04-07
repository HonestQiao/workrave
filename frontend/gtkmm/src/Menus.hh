// Menus.hh --- Main info Window
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 Rob Caelers & Raymond Penners
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $Id$
//

#ifndef MENUS_HH
#define MENUS_HH

#include "config.h"

#include <sigc++/trackable.h>

#ifdef HAVE_GNOME
#include <gnome.h>
#endif

#include "ICore.hh"

class GUI;
class TimeBar;
class NetworkLogDialog;
class NetworkJoinDialog;
class StatisticsDialog;
class PreferencesDialog;
class MainWindow;
class AppletWindow;
class ExercisesDialog;
class Menu;

using namespace workrave;

class Menus :
  public sigc::trackable
{
public:
  Menus();
  ~Menus();

  //! Menus items to be synced.
  enum MenuKind
    {
      MENU_NONE,
      MENU_MAINWINDOW,
      MENU_APPLET,
      MENU_NATIVE,
      MENU_SIZEOF,
    };

  enum
    {
      MENU_COMMAND_PREFERENCES,
      MENU_COMMAND_EXERCISES,
      MENU_COMMAND_REST_BREAK,
      MENU_COMMAND_MODE_NORMAL,
      MENU_COMMAND_MODE_QUIET,
      MENU_COMMAND_MODE_SUSPENDED,
      MENU_COMMAND_NETWORK_CONNECT,
      MENU_COMMAND_NETWORK_DISCONNECT,
      MENU_COMMAND_NETWORK_LOG,
      MENU_COMMAND_NETWORK_RECONNECT,
      MENU_COMMAND_STATISTICS,
      MENU_COMMAND_ABOUT
    };

  static Menus *get_instance();
  
  void init(MainWindow *main_windows, AppletWindow *applet_window);
  void applet_command(short cmd);
  void resync();
  void locale_changed();
  void popup(const MenuKind kind,
             const guint button,
             const guint activate_time);

private:
  void set_operation_mode(OperationMode m);
  
#ifdef HAVE_DISTRIBUTION
  void on_network_log_response(int response);
  void on_network_join_response(int response);
#endif
  void on_statistics_response(int response);
  void on_preferences_response(int response);
#ifdef HAVE_EXERCISES
  void on_exercises_response(int response);
#endif

  
public:
  // Menu actions.
  void on_menu_open_main_window();
  void on_menu_restbreak_now();
  void on_menu_about();
  void on_menu_quit();
  void on_menu_preferences();
  void on_menu_exercises();
  void on_menu_statistics();
  void on_menu_normal();
  void on_menu_suspend();
  void on_menu_quiet();
  void on_menu_network_join();
  void on_menu_network_leave();
  void on_menu_network_reconnect();
  void on_menu_network_log(bool show);

private:
  //! The one and only instance
  static Menus *instance;

  //! Interface to the GUI.
  GUI *gui;

#ifdef HAVE_DISTRIBUTION
  NetworkLogDialog *network_log_dialog;
  NetworkJoinDialog *network_join_dialog;
#endif

  // The Statistics dialog.
  StatisticsDialog *statistics_dialog;

  // The Statistics dialog.
  PreferencesDialog *preferences_dialog;

#ifdef HAVE_EXERCISES
  // The exercises dialog.
  ExercisesDialog *exercises_dialog;
#endif
  //! The main window.
  MainWindow *main_window;

  //! The applet window.
  AppletWindow *applet_window;

  //! Different kind of menus
  Menu *menus[MENU_SIZEOF];
};

#endif // MENUS_HH
