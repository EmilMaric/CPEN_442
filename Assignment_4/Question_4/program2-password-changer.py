import hashlib
import click


# Constants
PASSWORD_OFFSET = 0x127F3


@click.command()
@click.password_option()
def password_changer(password):
    """Changes the password for program2.exe"""

    hashed_password = hashlib.sha1(password)
    with open('program2.exe', 'r+b') as f:
        f.seek(PASSWORD_OFFSET)
        f.write(hashed_password.digest())
    print("Password changed successfully!")


if __name__ == '__main__':
    password_changer()
