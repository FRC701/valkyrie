#pragma once

#include <wpi/StringRef.h>

template <typename Preferences, typename T>
struct PreferenceTraits
{
  static T get(Preferences& prefs, const wpi::StringRef& key);
  static void put(Preferences& prefs, const wpi::StringRef& key, T value);
};

template <typename Preferences>
struct PreferenceTraits<Preferences, int>
{
  static int get(Preferences& prefs, const wpi::StringRef& key) 
  {
      return prefs.GetInt(key); 
  }

  static void put(Preferences& prefs, const wpi::StringRef& key, int value)
  {
    prefs.PutInt(key, value); 
  }
};

template <typename Preferences>
struct PreferenceTraits<Preferences, double>
{
  static double get(Preferences& prefs, const wpi::StringRef& key) 
  {
      return prefs.GetDouble(key); 
  }

  static void put(Preferences& prefs, const wpi::StringRef& key, double value)
  {
    prefs.PutDouble(key, value); 
  }
};

template <typename Preferences, typename T>
class Preference
{
  public:
    explicit 
    Preference(Preferences& prefs, const wpi::StringRef& key) : mPrefs(prefs), mKey(key) { }
    T get() const { return PreferenceTraits<Preferences, T>::get(mPrefs, mKey); }
    void put(const T& value) { PreferenceTraits<Preferences, T>::put(mPrefs, mKey, value); }
    operator T() const { return get(); }
    T operator=(const T& value) { put(value); return value; }

  private:
    Preferences& mPrefs;
    wpi::StringRef mKey;
};

