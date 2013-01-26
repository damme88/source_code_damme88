#include "stdafx.h"
#include "Personal_Info.h"

PersonalInfo::PersonalInfo(CString &name, int &old,
                           int &gender, CString &adress,
                           CString &major, CString &role) {
  name_ = name;
  old_ = old;
  gender_ = gender;
  adress_ = adress;
  major_ = major;
  role_ = role;
}

PersonalInfo::~PersonalInfo() {
  ;
}

int PersonalInfo::CheckGender(PersonalInfo &personal) {
  int check_gender = -1;
  check_gender = personal.gender_;
  if (check_gender == 1) {
    MessageBox(NULL, L"Gender is male", L"Check Gender", MB_OK|MB_ICONINFORMATION);
    return 1;
  }
  else if (check_gender == 2) {
    MessageBox(NULL, L"Gender is female", L"Check Gender",MB_OK|MB_ICONINFORMATION);
    return 2;
  }
  else {
    MessageBox(NULL, L"Gend is unknown", L"Check Gender", MB_OK | MB_ICONQUESTION);
    return -1;
  }
}
