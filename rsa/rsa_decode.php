<?php
$str = "catKiobfHK/w3chi0yWJiAQmdeMevoZZBJV+5gO7JBhwTkDwHpzyh1HzyVJlXGOM+G8VTndRFEGEYbXdaEBpBcqO68mX7j4+LU64g7TkXgYl4TL7wwzLu3lB9BpD/3XAkyVQhvjJCVA73crjr0mUNkKEBjjWbHdBu0/Q10gl4po=hXK44G2ph4uM9eNdV+GnZai832ne5GrRmgOIZUWJrNT/pfqnirfF7X3O5RXDC+ZLeNe5Sb5gDP66usWe2KaKVrXZ7Cc2PsL5WI/4z+MKY9SiTgqrwdAaaAOs8UZ6Z49/UsjsQkplgaRnaMyd6RDfFCaA+gQwwaoxVFbC7hvzDvY=WP/dAZ0VZdPBOx8KU61taNHqzaVoN7D0c5OYCaA7lsE2H1SzSfS2K8sdxXOcq6F2BF6bV7IQvIaEkLbbCCDEI+pXaXlBUHbW4OLOI/9ZO9HQiCoKtMb/FmEjCzu9xDLgww/IJo6mpMhXddg2P451W6mPLLeLVkw6M59KPJk6HLs=JwWybl+Z0JgsuzqPtXJSofuG4j4jk7upQoJLXvPBjmYyKtntheSOwwq81Pmmy6DzVbNKgy+SfqgfDcxWPeH4DDqFwIPISEXo/493f+VaeOnl0LQ5vBYZCKq2XcK/CuyLs+szEvN0TwvfAQ21faVMyEOuzkX8Q2OT5S6Z1wcci2A=R2FbK/3uOIo8+dCUM0UpsgiVXKhWC6fFpQ2wmL2QC692oJ6f0ZEZnvCmS+YJ4YRhUvVSwuLATHZp5RxKOa8PVNnz36LsXVu0/OxlOme1HnPMgi4JKeIo7SOfbq02onPJS+RDv/cU/55nGg0aYConl+1h9byt7jJs6DoDg6Jzn/c=Ru9C3YLu0MR8h1B0rqAoJGVemwnj1fmzrVpWTvyX9CJRFyDdTHNqsRGysf0yH5nUDOTTa9PfYo63+rRTAyljNUurf2x378RFQUqCPiI7/p6W2xNLuyxIWMUFNKdJLUTHr9dladUcuqElBuwLXEBTYOHZ4EdgV9uiYZEQVU8Sl1s=OdefUtmLi4EW/DRyPMjI70f7vXDJ1MbCzkHwfY8M3+X181nEq5CiC73B5+vW5eHtwRlrR2QqXENSMbyHRiney4L+1AIrGsF8wU8aC1XzyJaPkYj1RoCOadT648gQUU2Ovm1yleTvd0Y4Ogi/cNJTQx79q2CTt+zig1iY/a7TJ7k=CHGROiGd9fSTw4fHgDXNNM1KN0/l5lWh8l6OywsU0ADtCiwKYSO3SNG7j8dEeqFOx4pKmsn4NYIVlKhIwcxqwKoMti2zMGMZ8dLGRIIZfOcCfkd57fVIuRZ5d/3qK+LuZIxESznOEcMzLUgftbffSISOvipl7voHFjlaPZKJ+Ds=T6SVge7NmW7mDm10XT3fm9gB+Pl5T5epbSZGrkbhgYtOjNE46HPkTXIq3aRzGrSjQhJyb+Qntm8uYafzqebt6HBW2spo/VyqLkD1hqej6P6NHj6Ia/n7re+UrYD3JkmVqzp+IVLdCpLjmV3Ngrs6rf0+dbKkGd9nvqtSE5K/T+0=";

define("SPLIT_LEN", 172);

$pri_key = file_get_contents("./rsa_pri_key_1024.pem");

function decrypt_rsa($data, $pri_key)
{
    $decode_data = '';
    $split = str_split($data, SPLIT_LEN);// 1024bit  固定172
    foreach ($split as $part) {
        $isOkay = openssl_private_decrypt(base64_decode($part), $de_data, $pri_key);// base64在这里使用，因为172字节是一组，是encode来的
        if(!$isOkay){
            return false;
        }
        $decode_data .= $de_data;
    }
    return $decode_data;
}

$res = decrypt_rsa($str, $pri_key);
var_dump($res);