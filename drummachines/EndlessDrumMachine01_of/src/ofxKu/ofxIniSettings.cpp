#include "ofxIniSettings.h"

/*
ofxIniSettings - Released 22-1-2009 - by Rick Companje

Installation:
- Follow the regular openFrameworks methods for adding addons.

Notes:
- Have a look at the functions I copied from my ofxExtra addon
  like ofFileExists, ofSplitString and a lot of casting functions like ofToBoolean


Example Usage:

////////////////////////////////////////////////

ofxIniSettings ini;
ini.load("settings.ini");

cout << ini.get("myBoolean",true) << endl;
cout << ini.get("section1.myString",(string)"") << endl;
cout << ini.get("section1.myFloat",0.0f) << endl;
cout << ini.get("section1.myInteger",0) << endl;
cout << ini.get("section1.subsection.myInteger",0) << endl;
cout << ini.get("section1.myVec3f",ofxVec3f(0,0,0)) << endl;

ini.outputFilename="settings.ini";
ini.set("myBoolean",true);

//you can load an additional ini file to override certain settings by

ini.load("subsettings.ini",false);

//now values from subsettings overwrite existing values with the same name in the same section of settings.ini

////////////////////////////////////////////////

ini file layout:

;myBoolean is not inside a section but is on root level above the sections
myBoolean=1

[section1]
keyInsideSection1=this is a string value
myString=hello word
myFloat=1.0023424
myInterger=5
myVec3f=.001,.5,0
subsection.myInteger=6

[section1.subsection]
;overwrites subsection.myInteger=6
myInteger=7

[section2]
window=0,0,1024,768
*/


/* These functions are from my ofxExtras */
int die(string str) {
    cout << str.c_str() << endl;
    //_getch();
	ofSleepMillis( 1000 );
	OF_EXIT_APP(1);
    //std::exit(1);
}

bool ofFileExists(string filename) { //rick	
	ifstream inp;
	inp.open(filename.c_str(), ifstream::in);
	inp.close();
	return !inp.fail();
}

bool ofToBoolean(string str) { //rick 3-1-2008
	return str=="true" || str=="True" || str=="TRUE" || str=="1";
}



bool ofxIniSettings::load(string filename, bool clearFirst) {
    filename = ofToDataPath(filename);
    if (filename=="") die("ofxIniSettings::no filename");
    if (!ofFileExists(filename)) {
		//cout << "file not found: " + filename << endl; 
		die ("file not found: " + filename);
	}

    string cmd,section,key,value,id;
    ifstream f(filename.c_str(),ios::in);

    if (clearFirst) clear();

    while (getline(f,cmd)) {
		if ( !cmd.empty() ) {
	        switch (cmd[0]) {
	         case 0: break;   //empty first line?
	         case '#': break; //comment
	         case ';': break; //comment
	         case '[': 
					{
						size_t right = cmd.find( ']' );
						if ( right != string::npos ) {
							section = cmd.substr(1,int(right)-1); break; //section, remove brackets
						}
					}
				default:
	             int pos = cmd.find("=", 0);
	             if (pos==string::npos) break;
	             key = cmd.substr(0, pos);
	             value = cmd.substr(pos+1);
	             id = section!="" ? (section + "." + key) : key;
	             keys[id] = value;
	             //cout << "ini: " << id << " = " << value << endl;
	     }
   
		}
	}
    f.close();
    return true;
}

void ofxIniSettings::clear() {
    keys.clear();
}

string   ofxIniSettings::get(string key, string   defaultValue) { return has(key) ? keys[key] : defaultValue; }
int      ofxIniSettings::get(string key, int      defaultValue) { return has(key) ? ofToInt(keys[key]) : defaultValue; }
float    ofxIniSettings::get(string key, float    defaultValue) { return has(key) ? ofToFloat(keys[key]) : defaultValue; }
bool     ofxIniSettings::get(string key, bool     defaultValue) { return has(key) ? ofToBoolean(keys[key]) : defaultValue; }
//ofxVec2f ofxIniSettings::get(string key, ofxVec2f defaultValue) { return has(key) ? ofToVec2f(keys[key]) : defaultValue; }
//ofxVec3f ofxIniSettings::get(string key, ofxVec3f defaultValue) { return has(key) ? ofToVec3f(keys[key]) : defaultValue; }
//ofxVec4f ofxIniSettings::get(string key, ofxVec4f defaultValue) { return has(key) ? ofToVec4f(keys[key]) : defaultValue; }
//ofRectangle ofxIniSettings::get(string key, ofRectangle defaultValue) { return has(key) ? ofToRectangle(keys[key]) : defaultValue; }

void ofxIniSettings::setString(string newID, string newValue) {
    if (outputFilename=="") die("ofxIniSettings::setString: outputFilename undefined");
    bool foundKey = false;
    //outputFilename = ofToDataPath(outputFilename);
    if (!ofFileExists(outputFilename)) die("ofxIniSettings::setString: file not found: " + outputFilename);
    string cmd,section,key,value,id;
    ifstream fileInput(outputFilename.c_str(),ios::in);
    vector<string> lines;
	
	string newSection; 
	string newKey;
	{
		int i = newID.find(".", 0 );
		if ( i != string::npos ) {
			newSection = newID.substr( 0, i );
			newKey = newID.substr( i + 1 );
			//cout << "Section " << newSection << " key " << newKey << endl;
		}
	}

    while (getline(fileInput,cmd)) {
        switch (cmd[0]) {
            case 0: break;   //empty first line?
            case '#': break; //comment
            case ';': break; //comment
			case '[': 
				{
					string s = cmd.substr(1,cmd.length()-2); //section, remove brackets
					if ( section == newSection && !foundKey ) {
						foundKey = true;
						lines.push_back( newKey + "=" + newValue );
					}
					section = s;  
					break;
				}
            default:
                int pos = cmd.find("=", 0);
                if (pos==string::npos) break;
                key = cmd.substr(0, pos);
                id = section!="" ? (section + "." + key) : key;
                if (id==newID) {
                    foundKey=true;
                    cmd=key + "=" + newValue;  //change the value if found
                }
        }
        lines.push_back(cmd); //write to output list
    }
    fileInput.close();

	if (!foundKey) {
		//die("ofxIniSettings: Key '"+newID+"' should exist in '"+outputFilename+"'");
		lines.push_back("[" + newSection + "]");
		lines.push_back( newKey + "=" + newValue );
	}
    ofstream fileOutput(outputFilename.c_str(),ios::out);
    for (int i=0; i<lines.size(); i++) fileOutput << lines[i] << endl;
    fileOutput.close();
}

