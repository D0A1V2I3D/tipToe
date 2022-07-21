#include "app/appmain.h"
#include "initSDL.h"
#include "initDialog.h"

int main(int argc, char *argv[]) {
    init();
    int mode;
    dialog((int &) mode);
    App::mainapp(mode);
    return 0;
}
