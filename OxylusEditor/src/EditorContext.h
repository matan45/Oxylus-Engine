﻿#pragma once
#include <cstring>
#include <filesystem>

namespace Oxylus {
  enum class EditorContextType {
    None = 0,
    Entity,
    File,
    Asset
  };

  struct EditorContext {
    void Set(EditorContextType type, const char* data, size_t size) {
      delete[] m_Data;

      if (data && size != 0) {
        m_Type = type;
        m_Size = size;
        m_Data = new char[m_Size];
        memcpy(m_Data, data, m_Size);
      }
      else {
        m_Type = EditorContextType::None;
        m_Data = nullptr;
      }
    }

    void Reset() {
      Set(EditorContextType::None, nullptr, 0);
    }

    EditorContext() = default;

    ~EditorContext() {
      delete[] m_Data;
    }

    EditorContext(const EditorContext& other) {
      Set(other.m_Type, other.m_Data, other.m_Size);
    }

    EditorContext& operator=(const EditorContext& other) {
      Set(other.m_Type, other.m_Data, other.m_Size);
      return *this;
    }

    EditorContext(EditorContext&& other) = delete;
    EditorContext operator=(EditorContext&& other) = delete;

    [[nodiscard]] EditorContextType GetType() const { return m_Type; }

    template <typename T>
    [[nodiscard]] const T* As() const { return reinterpret_cast<T*>(m_Data); }

    std::string GetAssetExtension() const {
      const auto path = reinterpret_cast<std::string*>(m_Data);
      if (!path)
        return {};
      return std::filesystem::path(*path).extension().string();
    }

    [[nodiscard]] bool IsValid(EditorContextType type) const { return type == m_Type && m_Data != nullptr; }
    operator bool() const { return m_Type != EditorContextType::None && m_Data != nullptr; }
    bool operator==(const EditorContext& other) const { return m_Type == other.m_Type && m_Data == other.m_Data; }

  private:
    EditorContextType m_Type = EditorContextType::None;
    char* m_Data = nullptr;
    size_t m_Size = 0;
  };
}
