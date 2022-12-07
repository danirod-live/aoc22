#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Directory;

class Directory {
public:
  Directory() {}
  void SetParent(Directory *parent);
  Directory *Parent();
  Directory *GetDirectory(string &target);
  int Size();
  void AddFile(string &name, int len);
  void AddDirectory(string &name);
  void Dump();

  int P1();
  int P2(int req);

private:
  Directory *parent;
  map<string, Directory> children;
  map<string, int> files;
};

Directory *Directory::GetDirectory(string &target) { return &children[target]; }

void Directory::SetParent(Directory *pare) { this->parent = pare; }

Directory *Directory::Parent() { return this->parent; }

void Directory::AddFile(string &name, int len) {
  this->files[string(name)] = len;
}

void Directory::AddDirectory(string &name) {
  Directory d;
  d.SetParent(this);
  this->children[string(name)] = d;
}

int Directory::Size() {
  int total = 0;
  std::map<string, int>::iterator file_it;
  std::map<string, Directory>::iterator dir_it;
  for (file_it = files.begin(); file_it != files.end(); file_it++) {
    total += file_it->second;
  }
  for (dir_it = children.begin(); dir_it != children.end(); dir_it++) {
    total += dir_it->second.Size();
  }
  return total;
}

void Directory::Dump() {
  std::map<string, int>::iterator file_it;
  std::map<string, Directory>::iterator dir_it;

  cout << "<DIR> " << Size() << endl;
  for (file_it = files.begin(); file_it != files.end(); file_it++) {
    cout << "File: " << file_it->first << ", " << file_it->second << endl;
  }
  for (dir_it = children.begin(); dir_it != children.end(); dir_it++) {
    cout << "Dir: " << dir_it->first << endl;
    dir_it->second.Dump();
  }
  cout << "</DIR>" << endl;
}

int Directory::P1() {
  int total = 0;
  std::map<string, Directory>::iterator dir_it;
  for (dir_it = children.begin(); dir_it != children.end(); dir_it++) {
    int size = dir_it->second.Size();
    if (size < 100000) {
      total += size;
    }
    total += dir_it->second.P1();
  }
  return total;
}

int Directory::P2(int req) {
  int min = 70000000;
  std::map<string, Directory>::iterator dir_it;
  for (dir_it = children.begin(); dir_it != children.end(); dir_it++) {
    int size = dir_it->second.Size();
    if (size > req && size < min) {
      min = size;
    }

    int submin = dir_it->second.P2(req);
    if (submin > req && submin < min) {
      min = submin;
    }
  }
  return min;
}

class LineReader {
public:
  LineReader() : file("07.txt"), rewind(false) { getline(file, lastline); };
  string Previous() { return lastline; }
  string Line() { return line; }
  void Next();
  void Rewind() { rewind = true; }
  bool IsLsCommand();
  bool IsCdParentCommand();
  bool IsCdSubCommand();
  bool IsStdout();
  bool IsEof() { return eof; }

private:
  ifstream file;
  string line, lastline;
  bool eof, rewind;
};

void LineReader::Next() {
  if (rewind) {
    rewind = false;
  } else {
    if (!eof) {
      lastline = line;
      eof = !getline(file, line);
    }
  }
}

bool LineReader::IsLsCommand() { return line == "$ ls"; }

bool LineReader::IsCdParentCommand() { return line == "$ cd .."; }

bool LineReader::IsCdSubCommand() {
  return line[0] == '$' && !this->IsLsCommand() && !this->IsCdParentCommand();
}

bool LineReader::IsStdout() { return line[0] != '$'; }

int main(int argc, char **argv) {
  LineReader lr;
  Directory root;
  Directory *cwd = &root;

  while (!lr.IsEof()) {
    lr.Next();
    if (lr.IsEof())
      break;

    if (lr.IsCdParentCommand()) {
      cwd = cwd->Parent();
    } else if (lr.IsCdSubCommand()) {
      string target = lr.Line().substr(5);
      cwd = cwd->GetDirectory(target);
    } else if (lr.IsLsCommand()) {
      bool endOutput = false;
      while (!endOutput) {
        lr.Next();
        if (lr.IsEof()) {
          endOutput = true;
          break;
        }
        stringstream ss(lr.Line());
        if (lr.IsStdout()) {
          string first, second;
          getline(ss, first, ' ');
          getline(ss, second, ' ');
          if (first == "dir") {
            cwd->AddDirectory(second);
          } else {
            int tam = stoi(first);
            cwd->AddFile(second, tam);
          }
          // We have another entry
        } else {
          endOutput = true;
        }
      }
      lr.Rewind();
    } else {
      cout << "Socorro: " << lr.Line() << endl;
    }
  }

  cout << "P1: " << root.P1() << endl;

  // ^^^ por encima de esta línea solo dios sabe lo que ha pasado

  int used = root.Size();
  int total = 70000000;
  int free_ = total - used;
  int atleast = 30000000;
  int deletable = atleast - free_;

  cout << "Tengo que borrar " << deletable << endl;
  cout << "P2: " << root.P2(deletable) << endl;

  return 0;
}
