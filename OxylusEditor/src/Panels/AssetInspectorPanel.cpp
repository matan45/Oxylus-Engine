﻿#include "AssetInspectorPanel.h"

#include <icons/IconsMaterialDesignIcons.h>

#include <UI/IGUI.h>

#include "EditorLayer.h"
#include "Assets/AssetManager.h"

namespace Oxylus {
  AssetInspectorPanel::AssetInspectorPanel() : EditorPanel("AssetInspector", ICON_MDI_INFORMATION) { }

  void AssetInspectorPanel::OnUpdate() { }

  void AssetInspectorPanel::OnImGuiRender() {
    if (OnBegin()) {
      if (EditorContextType::Asset == EditorLayer::Get()->GetContext().GetType()) {
        if (EditorLayer::Get()->GetContext().GetAssetExtension() == ".oxmat") {
          DrawMaterialAsset(EditorLayer::Get()->GetContext().As<std::string>());
        }
      }
      OnEnd();
    }
  }

  void AssetInspectorPanel::DrawMaterialAsset(const std::string* path) {
    m_SelectedMaterial = AssetManager::GetMaterialAsset(*path).Data;
    InspectorPanel::DrawMaterialProperties(m_SelectedMaterial, true);
  }
}
