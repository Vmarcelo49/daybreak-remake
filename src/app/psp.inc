// --extract-psp=<iso>: the one run that writes files, and the only one that reads a disc.
//
// It finishes before SDL is initialised, before the GPU exists and before the settings file
// is read: a player who runs it wants psp-data/ beside the executable and nothing else. The
// files it collects are the PSP version's own (docs/psp/README.md); nothing here goes into
// git and nothing ships.

static bool runPspExtraction(const Options& options, std::string& error) {
    const char* base = SDL_GetBasePath();
    const std::string baseDir = base ? std::string(base) : std::string();
    const std::string manifestPath = psp::findPspManifest(baseDir);
    if (manifestPath.empty()) {
        error = "psp: cannot find assets/psp/manifest.txt, which lists the files to collect";
        return false;
    }
    try {
        psp::registerAllPspConverters();
        psp::PspManifest manifest = psp::PspManifest::load(manifestPath);
        psp::PspExtractOptions extract;
        extract.isoPath = options.extractPsp;
        extract.dataDir = options.pspData;
        if (extract.dataDir.empty())
            extract.dataDir = baseDir.empty() ? std::string("psp-data") : baseDir + "psp-data";
        extract.manifest = &manifest;
        std::cout << "psp: manifest " << manifestPath << ", " << manifest.entries.size()
                  << " files\n";
        const psp::PspExtractReport report = psp::extractPsp(extract, std::cout);
        std::cout << "psp: done: " << report.rawFiles.size() << " raw files and "
                  << report.converted.size() << " converted files in " << extract.dataDir
                  << '\n';
        return true;
    } catch (const std::exception& failure) {
        error = failure.what();
        return false;
    }
}
