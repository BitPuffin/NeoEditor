// generated by Fast Light User Interface Designer (fluid) version 1.0302

#include "MainWindow.h"
#include <FL/fl_message.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <MCore.h>
#include <fstream>
#include <algorithm>
extern std::string currentDirectory;
extern const char* fl_native_file_chooser(const char* title, const char* files, const char* dir, int type);
#if WIN32
#include <windows.h>
#endif

Fl_Double_Window* MainWindow::create_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(515, 459, "Project Manager");
    w = o;
    o->user_data((void*)(this));
    { project_browser = new Fl_Browser(0, 25, 195, 430, "Projects:");
      project_browser->type(2);
      project_browser->align(Fl_Align(FL_ALIGN_TOP_LEFT));
    } // Fl_Browser* project_browser
    { Fl_Group* o = new Fl_Group(200, 25, 310, 270, "Packages:");
      o->box(FL_ENGRAVED_FRAME);
      { package_browser = new Fl_Browser(205, 45, 155, 245, "Packages:");
        package_browser->type(2);
        package_browser->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      } // Fl_Browser* package_browser
      { Fl_Button* o = new Fl_Button(370, 260, 130, 25, "Install Package");
        o->callback((Fl_Callback*)install_package, (void*)(this));
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(370, 230, 130, 25, "Open Neo Store");
        o->callback((Fl_Callback*)open_neo_store);
      } // Fl_Button* o
      { Fl_Group* o = new Fl_Group(365, 35, 135, 185);
        o->end();
        Fl_Group::current()->resizable(o);
      } // Fl_Group* o
      o->end();
      Fl_Group::current()->resizable(o);
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(200, 315, 310, 135, "Projects:");
      o->box(FL_ENGRAVED_FRAME);
      { Fl_Button* o = new Fl_Button(205, 360, 150, 25, "Import Project");
        o->callback((Fl_Callback*)import_project, (void*)(this));
      } // Fl_Button* o
      { new Fl_Button(205, 330, 150, 25, "Create Project");
      } // Fl_Button* o
      { new Fl_Button(205, 415, 150, 25, "Copy Lua SDK");
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    o->end();
  } // Fl_Double_Window* o
  return w;
}

void MainWindow::open_neo_store() {
  // FIXME: Don't use system!!!
  #ifndef WIN32
  	system("./NeoStore");
  #else
  	ShellExecute(NULL, "open",
  			(currentDirectory + "\\NeoStore.exe").c_str(),
  			NULL,NULL, 1);
  #endif
}

void MainWindow::update_package_list() {
  // This file needs to be the same as in the NeoStore!
  	std::string confPath;
  #ifndef WIN32
  	confPath = getenv("HOME");
  	confPath += "/.neo-store/";
  #else
  	confPath = getenv("APPDATA");
  	confPath += "\\.neo-store\\";
  #endif
  
  	confPath += "installed.txt";
  
  	std::ifstream in(confPath.c_str());
  
  	if(!in)
  		return;
  
  	std::string line;
  	while(!in.eof())
  	{
  		line = "";
  		in >> line;
  		
  		if(!line.empty())
  			package_browser->add(line.c_str());
  	}
  
  	in.close();
}

void MainWindow::import_project(Fl_Button* btn, MainWindow* dlg) {
  const char* projectFile = fl_native_file_chooser("Choose a project", "*.mproj", 
  						NULL, Fl_Native_File_Chooser::BROWSE_FILE);
  
  if(projectFile == NULL)
  	return;
  
  dlg->addProject(projectFile);
  dlg->saveProjectList();
}

void MainWindow::install_package(Fl_Button* btn, MainWindow* dlg) {
  int value = dlg->project_browser->value();
  
  if(value <= 0)
  {
  	fl_message("You need to select a project!");
  	return;
  }
  
  std::string name = dlg->project_browser->text(value);
  
  if(name.empty())
  {
  	fl_message("You need to select a project!");
  	return;
  }
  
  std::string path = dlg->getProjectPath(name.c_str());
  
  if(path.empty())
  	return;
  
  // ATTENTION: Needs to be the same as in NeoStore!
  std::string package;
  
  #ifndef WIN32
  	package = getenv("HOME");
  	package += "/.neo-store/";
  #else
  	package = getenv("APPDATA");
  	package += "\\.neo-store\\";
  #endif
  
  value = dlg->package_browser->value();
  
  if(value <= 0)
  {
  	fl_message("You need to select a package!");
  	return;
  }
  
  std::string pkgName = dlg->package_browser->text(value);
  package += pkgName.erase(pkgName.find_last_of("-"));
  
  #ifdef WIN32
  	std::replace(package.begin(), package.end(), '\\', '/');
  	std::replace(path.begin(), path.end(), '\\', '/');
  #endif
  
  //fl_message("Copying %s to %s", package.c_str(), path.c_str());
  if(!copyDirectory(package.c_str(), path.c_str()))
  {
  	fl_message("Could not install package!");
  }
  else
  {
  	fl_message("Package installation was successful.");
  }
}

const char* MainWindow::getProjectPath(const char* name) {
  return m_projects[std::string(name)].c_str();
}

void MainWindow::addProject(const char* name, const char* path) {
  m_projects[std::string(name)] = path;
}

void MainWindow::loadProjectList() {
  std::string path;
  #ifndef WIN32
  	path = getenv("HOME");
  	path += "/.neo-project-manager/";
  #else
  	path = getenv("APPDATA");
  	path += "\\.neo-project-manager\\";
  #endif 
  
  if(!isFileExist(path.c_str()))
  	createDirectory(path.c_str(), true);
  	
  path += "projects.txt";
  
  std::ifstream in(path.c_str());
  
  if(!in)
  	return;
  
  std::string line;
  while(!in.eof())
  {
  	line = "";
  	in >> line;
  	
  	if(!line.empty())
  		addProject(line.c_str());
  }
  
  in.close();
}

void MainWindow::saveProjectList() {
  std::string path;
  #ifndef WIN32
  	path = getenv("HOME");
  	path += "/.neo-project-manager/";
  #else
  	path = getenv("APPDATA");
  	path += "\\.neo-project-manager\\";
  #endif 
  
  if(!isFileExist(path.c_str()))
  	createDirectory(path.c_str(), true);
  	
  path += "projects.txt";
  
  std::ofstream out(path.c_str());
  
  if(!out)
  	return;
  
  char sep;
  
  #ifndef WIN32
  	sep = '/';
  #else
  	sep = '\\';
  #endif
  
  for(std::map<std::string,std::string>::iterator iter = m_projects.begin(); iter != m_projects.end(); ++iter)
  {
  	out << iter->second << sep << iter->first << endl;
  }
  
  out.close();
}

void MainWindow::addProject(const char* filepath) {
  std::string path = filepath;
  
  int idx;
  #ifndef WIN32
  	idx = path.find_last_of("/");
  #else
  	idx = path.find_last_of("\\");
  #endif
  
  if(idx == -1)
  	return;
  
  std::string name = path.substr(idx+1);	
  path = path.erase(idx);
  
  project_browser->add(name.c_str());
  addProject(name.c_str(), path.c_str());
}