#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class FilePaths {
public:
    static void SetProjectRoot(const std::string& root) {
        s_projectRoot = fs::path(root);
    }

    static void SetProjectRootFromCwd() {
        s_projectRoot = fs::current_path();
    }

    static const fs::path& GetProjectRoot() {
        return s_projectRoot;
    }

    static std::string Resolve(const std::string& relative) {
        return (s_projectRoot / relative).string();
    }

    static fs::path ResolvePath(const std::string& relative) {
        return s_projectRoot / relative;
    }

    static std::string Assets() {
        return (s_projectRoot / "assets").string();
    }

    static std::string Shader() {
        return (s_projectRoot / "Shader").string();
    }

    static std::string Scripts() {
        return (s_projectRoot / "assets" / "scripts").string();
    }

    static std::string ToRelative(const std::string& absolutePath) {
        try {
            fs::path abs(absolutePath);
            fs::path rel = fs::relative(abs, s_projectRoot);
            return rel.generic_string();
        } catch (...) {
            return absolutePath;
        }
    }

    static std::string ToAbsolute(const std::string& relativePath) {
        fs::path rel(relativePath);
        if (rel.is_absolute()) return relativePath;
        return (s_projectRoot / rel).generic_string();
    }

    static bool IsAbsolute(const std::string& path) {
        return fs::path(path).is_absolute();
    }

private:
    inline static fs::path s_projectRoot = fs::current_path();
};
