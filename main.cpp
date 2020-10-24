#include <iostream>
#include "user.h"
#include "stream.h"
#include "admin.h"
#include "pastStream.h"
#include "streamZ.h"

using namespace std;

int main() {
    StreamZ site;
    site.init();
    /*try {
        Date d1(2002, 0, 2);
        cout << d1.getAge() << endl;
    }
    catch (DateIsNotValid& e){ cerr << e.what() << endl;}
     */
    return 0;
}
