#pragma once

#include <frc/Preferences.h>

template <typename T>
struct PreferenceTraits
{
  static T get(const wpi::StringRef& key);
  static void put(const wpi::StringRef& key, T value);
};

template <>
struct PreferenceTraits<int>
{
  static int get(const wpi::StringRef& key) 
  {
      return frc::Preferences::GetInstance()->GetInt(key); 
  }

  static void put(const wpi::StringRef& key, int value)
  {
    frc::Preferences::GetInstance()->PutInt(key, value); 
  }
};

template <>
struct PreferenceTraits<double>
{
  static double get(const wpi::StringRef& key) 
  {
      return frc::Preferences::GetInstance()->GetDouble(key); 
  }

  static void put(const wpi::StringRef& key, double value)
  {
    frc::Preferences::GetInstance()->PutDouble(key, value); 
  }
};

template <typename T>
class Preference
{
  public:
    explicit 
    Preference(const wpi::StringRef& key) : mKey(key) { }
    T get() const { return PreferenceTraits<T>::get(mKey); }
    void put(const T& value) { PreferenceTraits<T>::put(mKey, value); }
    operator T() const { get(); }
    T operator=(const T& value) { put(value); return value; }

  private:
    wpi::StringRef mKey;
};

