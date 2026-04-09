#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

static bool IsLetter(uint32_t cp) {
    return (cp >= 'A' && cp <= 'Z')
        || (cp >= 'a' && cp <= 'z')
        || (cp >= 0x0410 && cp <= 0x044F)   // А..я
        || cp == 0x0401                     // Ё
        || cp == 0x0451;                    // ё
}

static uint32_t ToLowerChar(uint32_t cp) {
    if (cp >= 'A' && cp <= 'Z') return cp + 32;
    if (cp >= 0x0410 && cp <= 0x042F) return cp + 0x20;
    if (cp == 0x0401) return 0x0451;
    return cp;
}

static bool DecodeUtf8CodePoint(const std::string &s, size_t &i, uint32_t &cp) {
    unsigned char b0 = static_cast<unsigned char>(s[i]);
    if (b0 < 0x80) {
        cp = b0;
        i += 1;
        return true;
    }
    if ((b0 >> 5) == 0x6 && i + 1 < s.size()) {
        unsigned char b1 = static_cast<unsigned char>(s[i + 1]);
        if ((b1 & 0xC0) != 0x80) return false;
        cp = ((b0 & 0x1F) << 6) | (b1 & 0x3F);
        i += 2;
        return true;
    }
    if ((b0 >> 4) == 0xE && i + 2 < s.size()) {
        unsigned char b1 = static_cast<unsigned char>(s[i + 1]);
        unsigned char b2 = static_cast<unsigned char>(s[i + 2]);
        if ((b1 & 0xC0) != 0x80 || (b2 & 0xC0) != 0x80) return false;
        cp = ((b0 & 0x0F) << 12) | ((b1 & 0x3F) << 6) | (b2 & 0x3F);
        i += 3;
        return true;
    }
    if ((b0 >> 3) == 0x1E && i + 3 < s.size()) {
        unsigned char b1 = static_cast<unsigned char>(s[i + 1]);
        unsigned char b2 = static_cast<unsigned char>(s[i + 2]);
        unsigned char b3 = static_cast<unsigned char>(s[i + 3]);
        if ((b1 & 0xC0) != 0x80 || (b2 & 0xC0) != 0x80 || (b3 & 0xC0) != 0x80) return false;
        cp = ((b0 & 0x07) << 18) | ((b1 & 0x3F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
        i += 4;
        return true;
    }
    return false;
}

bool Palindrome(const std::string &text) {
    std::vector<uint32_t> cleaned;
    size_t i = 0;
    while (i < text.size()) {
        uint32_t cp;
        if (!DecodeUtf8CodePoint(text, i, cp)) {
            // Пропускаем некорректные байты
            ++i;
            continue;
        }
        if (!IsLetter(cp)) {
            continue;
        }
        cleaned.push_back(ToLowerChar(cp));
    }

    return std::equal(cleaned.begin(), cleaned.begin() + cleaned.size() / 2, cleaned.rbegin());
}

int main() {
    std::string line;
    std::getline(std::cin, line);

    if (Palindrome(line)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NOtyu\n";
    }
    return 0;
}

