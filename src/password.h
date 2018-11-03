// generate_password() generates a password with 'prefix' as a prefix. 'prefix'
// must be null terminated.
//
// The password consists of the prefix, lower case letters, upper case letters,
// digits and punctuation characters.
//
// The password is generated using the system random generator arc4random and
// relies on its strength.
//
// The password is null terminated and placed in 'out' which must be long
// enough to hold the password.
//
// Assuming randomness of the underlying random generator arc4random, the
// entropy of the password is at least the entropy of the prefix plus 103. The
// entropy can be higher since the boundary between the prefix and the
// following characters is unknown from the password alone.
//
// The password is not constructed to obtain maximum entropy, given the length,
// but rather to satisfy standard password strength checkers. The password has
// the structure 'prefix' + 6 times ('punctuation character' + 'lower case
// letter' + 'upper case letter' + 'digit').  The password contains as long as
// the prefix doesn't and the prefix does not end with a punctuation character.
//
// The function is always successful. The return value is the length of the
// password excluding the null terminator. The length of the password is the
// length of 'prefix' plus 24.
int mk_generate_password(const char* prefix, char* out);
