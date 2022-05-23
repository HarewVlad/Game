void ImGuiManagerAndroid::Initialize(ANativeWindow *window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  // Disable loading/saving of .ini file from disk.
  // FIXME: Consider using LoadIniSettingsFromMemory() / SaveIniSettingsToMemory() to save in appropriate location for Android.
  io.IniFilename = NULL;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplAndroid_Init(window);
  ImGui_ImplOpenGL3_Init("#version 300 es");

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'docs/FONTS.md' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  // - Android: The TTF files have to be placed into the assets/ directory (android/app/src/main/assets), we use our GetAssetData() helper to retrieve them.

  // We load the default font with increased size to improve readability on many devices with "high" DPI.
  // FIXME: Put some effort into DPI awareness.
  // Important: when calling AddFontFromMemoryTTF(), ownership of font_data is transfered by Dear ImGui by default (deleted is handled by Dear ImGui), unless we set FontDataOwnedByAtlas=false in ImFontConfig
  ImFontConfig font_cfg;
  font_cfg.SizePixels = 22.0f;
  io.Fonts->AddFontDefault(&font_cfg);
  //void* font_data;
  //int font_data_size;
  //ImFont* font;
  //font_data_size = GetAssetData("Roboto-Medium.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
  //IM_ASSERT(font != NULL);
  //font_data_size = GetAssetData("Cousine-Regular.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 15.0f);
  //IM_ASSERT(font != NULL);
  //font_data_size = GetAssetData("DroidSans.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
  //IM_ASSERT(font != NULL);
  //font_data_size = GetAssetData("ProggyTiny.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 10.0f);
  //IM_ASSERT(font != NULL);
  //font_data_size = GetAssetData("ArialUni.ttf", &font_data);
  //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
  //IM_ASSERT(font != NULL);

  // Arbitrary scale-up
  // FIXME: Put some effort into DPI awareness
  ImGui::GetStyle().ScaleAllSizes(3.0f);
}

void ImGuiManagerAndroid::Shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplAndroid_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiManagerAndroid::RenderBegin() {
  // Poll Unicode characters via JNI
  // FIXME: do not call this every frame because of JNI overhead
  // PollUnicodeChars();

  // Open on-screen (soft) input if requested by Dear ImGui
  // static bool WantTextInputLast = false;
  // if (io.WantTextInput && !WantTextInputLast)
  //     Utility::ShowSoftKeyboardInput(app);
  // WantTextInputLast = io.WantTextInput;

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplAndroid_NewFrame();
  ImGui::NewFrame();
}