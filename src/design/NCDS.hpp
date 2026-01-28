#pragma once

#include <cstdint>
#include <string_view>

namespace nzt::gui::design {

    // -------------------------------------------------------------------------
    // 1. Primitives: Basic structures for Color and Font
    // -------------------------------------------------------------------------
    
    struct Color {
        uint8_t r, g, b, a;
        
        constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {}

        // Helper to create from Hex integer (e.g., 0xE61E2B)
        static constexpr Color fromHex(uint32_t hex, uint8_t alpha = 255) {
            return Color((hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF, alpha);
        }
    };

    enum class FontWeight {
        Regular = 400,
        Medium = 500,
        Bold = 700
    };

    struct FontSpec {
        std::string_view family;
        float size;
        float lineHeight;
        FontWeight weight;
    };

    // -------------------------------------------------------------------------
    // 2. Foundation: Color Palette (Based on Colors.pdf)
    // -------------------------------------------------------------------------
    namespace palette {
        //  Primary Red (NHN Commerce Identity)
        constexpr Color Red500 = Color::fromHex(0xEC1D31); // Primary Red
        constexpr Color Red600 = Color::fromHex(0xCF1722); // Hover state
        constexpr Color Red700 = Color::fromHex(0xB7131C); // Pressed state
        
        //  Grays (Neutrals)
        constexpr Color White  = Color::fromHex(0xFFFFFF);
        constexpr Color Gray50 = Color::fromHex(0xF8FAFC); // Background soft
        constexpr Color Gray100= Color::fromHex(0xF1F5F9);
        constexpr Color Gray200= Color::fromHex(0xE2E8F0); // Lines / Borders [cite: 136]
        constexpr Color Gray300= Color::fromHex(0xCBD5E1);
        constexpr Color Gray400= Color::fromHex(0x94A3B8);
        constexpr Color Gray500= Color::fromHex(0x64748B); // Muted text
        constexpr Color Gray600= Color::fromHex(0x475569);
        constexpr Color Gray700= Color::fromHex(0x334155); // Main Text
        constexpr Color Gray800= Color::fromHex(0x1E293B);
        constexpr Color Gray900= Color::fromHex(0x0F172A);
        constexpr Color Black  = Color::fromHex(0x000000);

        // [cite: 140-144] Semantic Colors
        constexpr Color Green500  = Color::fromHex(0x22C55E); // Success
        constexpr Color Orange500 = Color::fromHex(0xF97316); // Warning
        constexpr Color Blue500   = Color::fromHex(0x3B82F6); // Info / Link
        constexpr Color Violet500 = Color::fromHex(0x8B5CF6); // Accent [cite: 144]
    }

    // -------------------------------------------------------------------------
    // 3. Foundation: Typography (Based on Typography.pdf)
    // -------------------------------------------------------------------------
    namespace typography {
        //  Font Families
        constexpr std::string_view FontFamilySans = "Commerce Sans";
        constexpr std::string_view FontFamilyInter = "Inter";

        // [cite: 423-431] Display Styles
        constexpr FontSpec DisplayXL_Bold   = { FontFamilySans, 48.0f, 60.0f, FontWeight::Bold };
        constexpr FontSpec DisplayLG_Bold   = { FontFamilySans, 36.0f, 44.0f, FontWeight::Bold };
        constexpr FontSpec DisplayMD_Bold   = { FontFamilySans, 30.0f, 38.0f, FontWeight::Bold };
        
        // [cite: 440] Body Text Styles
        constexpr FontSpec TextLG_Regular   = { FontFamilyInter, 18.0f, 28.0f, FontWeight::Regular };
        constexpr FontSpec TextMD_Regular   = { FontFamilyInter, 16.0f, 24.0f, FontWeight::Regular };
        constexpr FontSpec TextSM_Regular   = { FontFamilyInter, 14.0f, 20.0f, FontWeight::Regular };
        constexpr FontSpec TextXS_Regular   = { FontFamilyInter, 12.0f, 18.0f, FontWeight::Regular };
    }

    // -------------------------------------------------------------------------
    // 4. Components: NCDS Token Mapping
    // -------------------------------------------------------------------------
    namespace tokens {
        
        // --- Global Layout ---
        constexpr float BorderRadiusSmall = 4.0f;
        constexpr float BorderRadiusMedium = 8.0f; // Standard for Inputs/Buttons [cite: 295]
        constexpr float BorderRadiusLarge = 12.0f; // [cite: 153]

        // --- Buttons [cite: 14, 53-56] ---
        struct ButtonTheme {
            Color background;
            Color text;
            Color border;
            Color backgroundHover;
            Color backgroundPressed;
        };

        // Primary Red Button (Solid)
        constexpr ButtonTheme ButtonPrimary {
            /* bg */      palette::Red500,
            /* text */    palette::White,
            /* border */  palette::Red500, // Same as BG
            /* hover */   palette::Red600,
            /* pressed */ palette::Red700
        };

        // Secondary Button (Outline/White) [cite: 15]
        constexpr ButtonTheme ButtonSecondary {
            /* bg */      palette::White,
            /* text */    palette::Gray700,
            /* border */  palette::Gray300,
            /* hover */   palette::Gray50,
            /* pressed */ palette::Gray100
        };

        // Button Sizes [cite: 59-63]
        constexpr float ButtonHeightMD = 44.0f; // Standard
        constexpr float ButtonHeightSM = 36.0f;
        constexpr float ButtonHeightXS = 30.0f;

        // --- Inputs [cite: 293-314] ---
        struct InputTheme {
            Color background;
            Color text;
            Color placeholder;
            Color border;
            Color borderFocus;
            Color borderError;
        };

        constexpr InputTheme InputDefault {
            /* bg */          palette::White,
            /* text */        palette::Gray900,
            /* placeholder */ palette::Gray400, // [cite: 311]
            /* border */      palette::Gray200,
            /* focus */       palette::Red500,  // Focus usually takes Primary color or distinct ring
            /* error */       palette::Red500   // [cite: 315] Destructive
        };

        constexpr float InputHeight = 44.0f; // Matches Button MD

        // --- Toggles [cite: 391-410] ---
        struct ToggleTheme {
            Color trackOff;
            Color trackOn;
            Color thumb;
        };

        constexpr ToggleTheme ToggleSwitch {
            /* off */   palette::Gray300,
            /* on */    palette::Red500, // Primary color when active
            /* thumb */ palette::White
        };

        // --- Checkboxes & Radios [cite: 78, 356] ---
        struct ControlTheme {
            Color borderUnchecked;
            Color backgroundChecked;
            Color checkmark;
        };

        constexpr ControlTheme CheckboxDefault {
            /* border */ palette::Gray300,
            /* bg */     palette::Red500, //  Accent color
            /* mark */   palette::White
        };
    }
}