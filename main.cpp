#include <iostream>
#include <fstream>
#include "radix64.h"

int main() {

    /*
     * Test conversion from radi64
     *
     * Key Tested: Szymon Drabkowski <ozzyman@yoyo.pl>
     * Url Key: http://pgp-srv.deib.polimi.it/pks/lookup?op=get&search=0x853A96ED59239DF0
     * */

    std::string arm =
            "mQGiBDl+n2gRBAD1YZVdYRJmcPfTg7jiZuwPRVL1MKBWbLYhRdW2Qn6WN/e74yDxlvmI+OTj\n"
            "D7hjECTR7QlLZkh6B+ICoadTx6/fODDnZLJTA7acG+DrdCzRc2TAemT4ybJfB7OuyjCXAXzU\n"
            "Kkddn8DuDfbYa+d8xjHXb5YlBDjXvhOK/kYEpxO5GQCg/wTMJaco4dBEx31T+qbqWlqKSqsE\n"
            "AITnmwscgmj4zGTx4D4cqgRIBDq1hLVc7TpQwMdoYRPvCHeY7rdkrAzO4p7GkmCImCcg8Mby\n"
            "COzEkFNnk2jUCxOK6CEtzxWD5NDN8bgtyrcY6u3j+xlstdV8zOnN3otPHZocX+zqAMjPwveH\n"
            "ryHVL8HYQ9NS/RAAVOiQL0V4ep+qBAChH2V5GdLKNWBheoZR6cyO2ncn66ND9DssBtsRm1Gk\n"
            "f5yUmW7gwlbigJY8feCuxrvCMATTernzEm6ry/M0GZ/YgemLHHdgvZSthxv9QORAoejlZI2v\n"
            "eAtrWQzF+qeW0X4W4IxwbCZu1lbKvjt71mbO/u65GRpSYKt0B8FYG00QvLQjU3p5bW9uIERy\n"
            "YWJrb3dza2kgPG96enltYW5AeW95by5wbD6ITgQQEQIADgUCOX6faAQLAwIBAhkBAAoJEIU6\n"
            "lu1ZI53wkhEAoN+I5iJ1KT4rMNMZeCVCNqvQ2wZUAJ9F7a6OjDfIfstnJFVMgGhy+N9L8NH/\n"
            "AAAMsP8AAAyrARAAAQEAAAAAAAAAAAAAAAD/2P/gABBKRklGAAEBAAABAAEAAP/bAEMACgcH\n"
            "CAcGCggICAsKCgsOGBAODQ0OHRUWERgjHyUkIh8iISYrNy8mKTQpISIwQTE0OTs+Pj4lLkRJ\n"
            "QzxINz0+O//bAEMBCgsLDg0OHBAQHDsoIig7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7\n"
            "Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7O//AABEIAHEAeAMBIgACEQEDEQH/xAAfAAABBQEBAQEB\n"
            "AQAAAAAAAAAAAQIDBAUGBwgJCgv/xAC1EAACAQMDAgQDBQUEBAAAAX0BAgMABBEFEiExQQYT\n"
            "UWEHInEUMoGRoQgjQrHBFVLR8CQzYnKCCQoWFxgZGiUmJygpKjQ1Njc4OTpDREVGR0hJSlNU\n"
            "VVZXWFlaY2RlZmdoaWpzdHV2d3h5eoOEhYaHiImKkpOUlZaXmJmaoqOkpaanqKmqsrO0tba3\n"
            "uLm6wsPExcbHyMnK0tPU1dbX2Nna4eLj5OXm5+jp6vHy8/T19vf4+fr/xAAfAQADAQEBAQEB\n"
            "AQEBAAAAAAAAAQIDBAUGBwgJCgv/xAC1EQACAQIEBAMEBwUEBAABAncAAQIDEQQFITEGEkFR\n"
            "B2FxEyIygQgUQpGhscEJIzNS8BVictEKFiQ04SXxFxgZGiYnKCkqNTY3ODk6Q0RFRkdISUpT\n"
            "VFVWV1hZWmNkZWZnaGlqc3R1dnd4eXqCg4SFhoeIiYqSk5SVlpeYmZqio6Slpqeoqaqys7S1\n"
            "tre4ubrCw8TFxsfIycrS09TV1tfY2dri4+Tl5ufo6ery8/T19vf4+fr/2gAMAwEAAhEDEQA/\n"
            "API6Py4oOKKo0CkpaciM5wBk0AIATVq3tPMZfMJVT1OK09L0uJ2HnYBIzycAVrzQ6BaMI7q4\n"
            "cy4+5F0H41zzrWdkWonO3EFnEdqIzn1ziqQCBvmyAK6G90eWaEXdpGGgJ4G75vyrPl0i68xQ\n"
            "kLMSM4AohUTW43FlQLG5+WMt7Zpr2b4yEYfWt2G30q0QRajbzpKOSRxTRf6dbSMIXeSI5+SR\n"
            "c4pe0fRC5TnXidOGUimVtzR2dwoML8k9G7VlzwGJz6eua1jO5LViCilPWkxWghOlFFFAC0UU\n"
            "uCMZoAQDJwOprd022W1LSOgdoxlgegNY0DbJVbuDkVqTXLxWBTYweWTc7HuPSsal3oi423E1\n"
            "BLhLrLkhXG5cdxWhpHhXUNRuoy8W1W+cs+QCK1dI0W1e0g1XUJy0ELfvI+23tivS/Dmnya8s\n"
            "WpOot7HI8qFRguF6Z9q4qmIklyw3N1BL3pbGZY+GLySxgRYI4lTjBHJ960o/B5tlZowDKw69\n"
            "q7cIAAAMAU7Fc6oTfUzdfyPJ9d8FXd67i4Rj8ny7RzmvOZdGksb2S2u4G2jI3Yx9DX06yA9R\n"
            "XnnxCMFpJHC1mha54SXGMe1aJ1KOj1TLjJVHtqeIKklrd4Yd8HIreuPD80ibkGA67lB71uab\n"
            "ZaZrFvtvAsFyrlMkcHB7VLqSyaXaNbmcFUbKYPT6GtpV22ktxcllqeczRtHIyMCGU4IqI81o\n"
            "ak3m3byHBLHOR3qgR6V3xd0YNCDnvRSUVQhyY3DI4zV65s2BBjjYpzg46iqceN4z0rp47uOz\n"
            "tImjRJoZRiSJmzhvw6VjUk4tWLik9zmolInUY711sUdhevEl1+7iKDJAwc4Fc688BuQ0UJQB\n"
            "s7S2cV08WnxXENsiODJKi5A7HArCvLZvQ1px1Oo0Lw1HqzQWAvv+JeFLPEp+ZsH5efx/SvWb\n"
            "O2hs7aO2gQJHGoVVHYCvK/h9bTWuuRRMxziQFT/dwP616ygNcFJydXuVidLIkoxQKWvYSOEQ\n"
            "1la/oFj4hsDa3iHjlJF4ZD6itWo3kjT7zqPqaxr2tqyotp3R494i8Iy+HbZWEytHv4fGD+Nc\n"
            "jqtxctbM0zCROgO7Jr27xQ1nc6bIs4WSJRuODXis9jDdSefsKW2/aBnkivOoTTk79D0bOUEz\n"
            "l3LuhYDKKcVEuArEjOa0tRWCzn8q3YtGGJwetUJ/LZiYwQp6AnpXrRldHJJWZXxRTyuBRWhm\n"
            "NXrXRwrbzWQhjbaqqCXPdu9c2Dg1PE7cKr4J9TgVFSPMXF2LF7YyWd00Z+YdUcdGHqK3fCdz\n"
            "L/acIK+YIznbnBxXP/apUIRm3bDlc84rZsNVMhRFsIWmXkSKNp4rCspOFrG1Oykel6TFZ3Ou\n"
            "+atw9viM7hGSDzyRmuoe5EKj7Pqzx84XzTkE1heDtJF/INRvWzLt2iNOFH+JrrxoVjJZ/ZJY\n"
            "VeMPvHqD65rxYw5p2udNWpCOjHade3bRIboK6PgrKnQg9K1C2FzVK8Edvp+xVCrGoVAOw7Ui\n"
            "Ts9ijjkkDNdca8qPNBu+hxSjz+8lYqXqXbpLPI8ghiUsVTgkdabaXsUtuJEtCYg+zewBye/P\n"
            "PetiM74x7jkUghRFCKiqg6KowBS+rpw503dj9t9loxtT02K5t5FEQCyLggdPyrxnXrGSzhnM\n"
            "jNDHHIVRQvVu9e66k7RWMrx43quVz614XqWsJdw3EGqTuroWeOIL1c+prOjFxqNI6ac26bbO\n"
            "Pkty2XaQAYzz1qsxAPy9K0rmzP2ZJVkyZf4T1qlJD5Zx1xXsxlc5JIvWOjPeJvLgDvxRWtp9\n"
            "ytnuEpEaYBx6cCiuSdSrze7sdlOnScdTkcULyQKDRXonnlkJ5TgsnIw2D3FbXhtIbzxFbRTy\n"
            "LFFIxVmPTkHA/PFYHmFsBj0GBVmIQeVzMyS54Xbx9c1jON4tGkHZ3PcfBUr27T2jMC0UpBI7\n"
            "130YJAJryH4azS3MG5JN0qEqxJ5Net28peFWIwe9ePTtCu1I3xCvGMkVtWG9IoV+9I2BVlYN\n"
            "tsqDjAxUNzCl0yESlWTOCvNTEXBQIXUY6uOp/CqSjKpOVtzFv3Iq4tod0fIIIOKmYcU2JRGu\n"
            "Cck8k0rniuyCUKFnuYvWWhl61LssmUDJbivHfiAukSXUNtpfkzz+WC7xOCQ2TnOK9S8V3Isd\n"
            "Oe4Zvugkfka+eYCftDyshkYk5AODn1zXLhoOUnPsdalywS7mnpsENpC5ubdt/UFzis6V0nuw\n"
            "oGAW4xUU9zOzFNzhemGOf51B5oGCPlPTI616MYO7bM3JbI2ZAzXuyMkKVwcHqKKvWKBLUzOg\n"
            "LFQF4ztorlc3eyPQp0ly3ZxxpKWkNemeSAODU8U6oclcnoKgoAJpNXGnY7v4Za2NP1420zBY\n"
            "7gfKfRv8/wAq92tmS5tnUMQQSODXytHPJEgVHKjcH4PcdDXsngDx9HfwpaXrhLxF2knAEi9i\n"
            "PevKxlFqXtUrrqdEPfjy9VsdhcTX+m3A8lVlh7ZHIq/FrDPCZHt2AX71W40WQCRcFWGSOtSi\n"
            "NcY2j8q5qKkloOdWEklKOpXtbuW6ywhMadiT1qyWwvNB+VcnAAqlPO7oUhOGIyW/uj/Gqc3D\n"
            "R7mNud6KyOC+I2soEitiSwL/ADgenOP5V5i8dvbaf5plHmOc4HUda1PGms+dq05iG4KxQOR0\n"
            "wTmuS+aaJmJPHtXZhqdoJmtR2dhs8pcqSc8fnSWsEl1MI4+W61E3LfStXSYTFOkg5BHWuyb5\n"
            "Y6GUI80rG3p16qjyJ12OBgqwoq7LaQ3MKyPGGbHUHBory24t3PTUpLQ4CiiivZPIDFLtyetF\n"
            "KOtAHefDLwrpfiOa9fUDva1ClYc43A55/DH611Y8K6bda8bQW6xReTiN4htaNtxwQR+Fea+E\n"
            "vEc/hfXY7+MF42UxzRg/fQ9R9eAfwr3TRjZauF1bT5RLE/3SPTuD6HPavHxvtIzunozqouPL\n"
            "qQaVq114YA0rxAz+Shxb35U+XIvbJ/hPbBrpo9W06SHzkvbdoz/EJBipzFHNCY5UWRGGGVhk\n"
            "H6iqsegaNE26PSbJG65W3QH+VOnCdrxZjKcJayWoNeC9j2WYMit1l/hH0PekulW109+cnHJP\n"
            "c1fCqqgKAAOgFZusL5sIgUbix5FY14NJyk9SqbvJJbHhviXT3u9RmYJy0hKnHXk8e9c/cW32\n"
            "BGjcqSRzgcg10vxF1CODVF020Knyhuldeu45IGfxP51xFxdTT8SSM+PU5rvw8JuCvsVUmrsh\n"
            "OSxPNaOj38dpchLjPkt1OPu+9Z3NJnNdkoqSszCMnF3R6GdgtDLHKHQDO5TniiuHtdTurRdk\n"
            "chMf9xuRRXD9VkvM7PrEWVKWiivQOIDThRRSAWvZvgl/yDdQ/wCuo/lRRXLi/wCGXHqepJUl\n"
            "FFZ4f4DJ7iGsTXv+PS6/64P/AOgmiiscV8KNqHxHzZqn/H4P+uaf+giqDdPwoor0o7Il7irT\n"
            "e9FFUQFFFFMpH//ZiEsEEBECAAsFAjmGrPcECwMCAQAKCRCFOpbtWSOd8Gw+AKCsd5izZIbP\n"
            "ApvVQXIYHFi8HcnllgCdHTHmxvT3t5MR2r6EoeLoyGBn2Ke5Ag0EOX6faBAIAPZCV7cIfwgX\n"
            "cqK61qlC8wXo+VMROU+28W65Szgg2gGnVqMU6Y9AVfPQB8bLQ6mUrfdMZIZJ+AyDvWXpF9Sh\n"
            "01D49Vlf3HZSTz09jdvOmeFXklnN/biudE/F/Ha8g8VHMGHOfMlm/xX5u/2RXscBqtNbno2g\n"
            "pXI61Brwv0YAWCvl9Ij9WE5J280gtJ3kkQc2azNsOA1FHQ98iLMcfFstjvbzySPAQ/ClWxiN\n"
            "jrtVjLhdONM0/XwXV0OjHRhs3jMhLLUq/zzhsSlAGBGNfISnCnLWhsQDGcgHKXrKlQzZlp+r\n"
            "0ApQmwJG0wg9ZqRdQZ+cfL2JSyIZJrqrol7DVekyCzsAAgIH/2vlMzr7k+Qrbhf8aYaStzB5\n"
            "7rHZGuTnMExB7IlzlG2JhrzH20Bpq1YJpKjvxZ5ZQmvcDs7cDJI40e1bLTotX64vWs8ua6hg\n"
            "955OlDid459ce34zG0Efyvps4sSIZ7rzKHytu7fuwDXloWWFMMuxWJVBorwVK3H/Bo7Y3SBU\n"
            "Knr4CqXfIJOlv25jOTad8iLODUcX5z/KcPU4wSluirxJ2v9e+R0d6QZa2KJE/99CZqO35gir\n"
            "gy8S/o6p+O5Vy+tNO7JDN0Fvhec0QdNnm+TfrR0yPqZNF8J4PROro2pT6AfWMifgbzHOoFAh\n"
            "3GqIQbZ1S4tdIKa3DI9LnWz+4ckWpx+IRgQYEQIABgUCOX6faAAKCRCFOpbtWSOd8Lh2AKCu\n"
            "0GhXtvXsQtPlnXgRMmOQ/lqJVACdEuWXdf20ZD+Rnbat7pVZLoMege4=\n";
    /* Removed anything useless */


    std::string body;
    std::string line;
    std::stringstream s(arm);
    while (std::getline(s, line)){
        body += line;
    }
    std::ofstream myfile;
    myfile.open ("../KeyBin_LibOpenPGP.asc", std::ios::binary);
    myfile << Radix64::radix642ascii(body);
    myfile.close();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}