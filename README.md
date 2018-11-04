# Authenticated encryption and decryption of files of secrets

This repository contains code for encryption and (authenticated) decryption of
files containing secrets. A password generator is also included.

# Rationale for this repository.

In a modern world, an enormous number of passwords, secrets, and codes are
needed. For many people, including the author of this repository, it is a
problem to remember all the secrets. Passwords are needed for mail, social
media, banks, survey sites, school, work, web shops, etc. Other types of codes
are needed to unlock phones, doors, WiFi access, etc.

One possible solution is to reuse the same password again and again. This is
however very insecure, since a breach of one service could lead to
vulnerabilities in other places. Also, it is impossible to know how a web
service handles passwords.  They might even sell them. There are also secrets
that are impossible to change such as an entry code.

The only viable solution is hence to "remember" a plethora of secrets. 
Password managers such as Last Pass or Dash Lane is a possible solution. 
One creates an individual password for every service and protects it with a 
master password.

Standard password managers work for some people in certain cases. 
Personally I found them too heavy and intrusive. One
also needs to trust their implementations and procedures.

The simplest and most efficient solution for me is to have a single file with all the secrets.
For example

    My secrets:

    Mail: mk@amberbio.com password:abcdef
    Bank: morten, 123Whatever
    Mobile Phone1: number: 123456, pin code: 4456
    Mobile Phone2: number: 123456, pin code: 9876

    Daughter's phone: pin code 8765
    social security number: 123456789

    Bank codes: 2343 3232 2221 9871 ....

    Bank box entry code: abcd345

All secrets and any other information is kept in a single, or several, files.
This makes it fast and easy to search for information, create new fields and 
update existing fields.

There are three obvious problems with a file of secrets. Firstly, if the file is
read by an unauthorized person, all secrets are exposed. Secondly, if the
computer with the file of secrets breaks down or is lost, all the secrets are
lost. Thirdly, the file is only available at one computer.

Actually, the first problem might not be so serious. A computer should be
protected from unauthorized access in any case, and the file of secrets can be
hidden in some obscure directory. It is unlikely that a physical intruder will
find the file, or even look for it. Also, one can solve the first problem with an
encrypted file system. However, the two other problems are serious in my opinion.
One cannot accept loss of the file of secrets because a hard disk breaks down
or a computer is lost, and one needs to access the secrets at more than one device.

All these problems are solved with encryption. By encrypting the file of
secrets with a master password, the file can be sent anywhere. The encrypted
file of secrets can be checked into version control, it can be uploaded to
cloud storage, or it can simply be emailed to oneself or to others. As long as
one trusts the encryption it is easy to ship it around.

Having a file of secrets makes it feasible to use much more complex passwords
for all services. Filling in a password becomes a copy-paste operation instead
of manual typing. Passwords should look more like "+qY1@uC2@qT2^xI2&oA5+uV3"
rather than "Alex1985". Such high strength passwords are not
vulnerable to dictionary attacks.

The purpose of the code in this repository is to provide a very simple set of
tools for managing this problem. Three commands are provided: "encrypt",
"decrypt", and "password".

"encrypt" encrypts a file with a key. The encryption is authenticated, meaning
that tampering can be detected as well.

"decrypt" authenticates and decrypts the file again. The original file (of
secrets) will be recovered.

"password" generates a high strength password with any user supplied prefix.

There is nothing fancy about the tools supplied here. They are just made for
convenience for the author, and hopefully someone else. The underlying
principle of this design is simplicity.

# Usage

There are three commands "encrypt", "decrypt" and "password".

* "encrypt" encrypts the input file, using a secret key, and writes the result
  into an output file.
* "decrypt" authenticates an input file and depending on the result of
  authentication, decrypts the file or reports an authentication error.
* "password" generates a random password with a given prefix.

Command line usage:

    Usage: bin/encrypt [-h] -k string -i input -o output
      -h, --help    display this message
      -k, --key     secret key for the authentiated encryption
      -i --input    file path of data to encrypt
      -o --output   file path of encrypted data

    Usage: bin/decrypt [-h] -k string -i input -o output
      -h, --help    display this message
      -k, --key     secret key for the authentiated encryption
      -i --input    file path of data to decrypt
      -o --output   file path of decrypted data

    Usage: bin/password [-h] [-p string]
      -h, --help    display this message
      -p, --prefix  prefix for the password(max length 50)

The secret key used for encryption/decryption is a null terminated string and
hence should not be a binary. A key generated by the password command could be
used. Alternatively, a long passphrase would be suitable.

# Cryptographic details

The encryption and decryption is done with the Keyak Authenticated Encryption
with Associated Data (AEAD) method. Internally, Keyak uses the Keccak permutation
also used for the elegant SHA3 hash function.

We believe that this encryption method is very strong, and that it will be infeasible
for anyone to break or alter the encrypted data under the assumption that the
key is safe.

# External dependencies

The only external dependency is the eXtended Keccak Code Package (XKCP)
https://github.com/XKCP/XKCP.

# Building the executables

After cloning the repository, the XKCP submodule should be updated.

    git submodule update --init

Move into the XKCP directory and build the keccak libary:

    cd XKCP
    make generic64/libkeccak.a

Move back into the build directory and invoke ninja:

    cd ..
    cd build
    ninja

Ninja must be installed. If ninja is not available, it is possible to execute
the commands in build.ninja manually or write an equivalent Makefile. Please,
open an issue if other build options are wanted.

The binaries are now located in build/bin

    > ls bin
    decrypt		encrypt		password	test

# Installation

The binaries are statically linked and can be copied to any installation
directory such as /usr/local/bin. Alternatively, the build/bin directory can
be added to PATH.

# Testing

Run build/bin/test from the root directory after building.

    ./build/bin/test
    All tests passed

# Supported platforms

The code is tailored to Unix/Linux/Mac environments. However, the C standard
library is used in most places, and minor adjustments, if any, should be enough
to make the code work on other platforms.

# Language

All code is written in C.

# License

The code in this repository is released in the public domain.  The relevant third
party code from XKCP is released in the public domain, to our understanding.
