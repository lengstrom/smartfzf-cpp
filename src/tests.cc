Test::Test(int h) {
    std::cout << h << std::endl; //flushes output buffer
}

Test::~Test() {
    std::cout << "Destruction." << std::endl;
}


int main(int argc, char * argv[]) {
    Test foo(5);
    std::cout << "Smartfzf file size: "<< boost::filesystem::file_size("smartfzf") << "\n\n";
    std::cout << "Does aj match Abchasj? " << bts(foo.fz_match("aj","Abchasj")) << '\n';
    std::cout << "Does aaj match Abchasj? " << bts(foo.fz_match("aaj","Abchasj")) << '\n';
    std::cout << "Does sj match Abchasj? " << bts(foo.fz_match("sj","Abchasj")) << '\n';
    std::cout << "Does abas match Abchasj? " << bts(foo.fz_match("abas","Abchasj")) << '\n';
    std::cout << "Does abash match Abchasj? " << bts(foo.fz_match("abash","Abchasj")) << '\n';
    std::cout << "Does chj match Abchasj? " << bts(foo.fz_match("chj","Abchasj")) << '\n';
    std::cout << "Does na match Abchasj? " << bts(foo.fz_match("na","Abchasj")) << '\n';

}

const char *bts(bool input)
{
    return input?"true":"false";
}

