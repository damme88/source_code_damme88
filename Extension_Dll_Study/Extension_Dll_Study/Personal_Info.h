#ifndef PERSONAL_INFO_H_
#define PERSONAL_INFO_H_

class __declspec(dllexport) PersonalInfo {
private :
  CString name_;
  int old_;
  int gender_;
  CString adress_;
  CString major_;
  CString role_;

public:
  PersonalInfo(CString &name, int &old,
               int &gender, CString &adress,
               CString &major, CString &role);
  virtual ~PersonalInfo();
  int CheckGender(PersonalInfo &personal);
};
#endif // PERSONAL_INFO_H_