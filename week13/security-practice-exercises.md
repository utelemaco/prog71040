# Linux Security Commands - Practice Exercises

**Note: In the remainder of this file, the workspace directory `~/prog71040/security_lab` can be any directory of your choice.**

## Exercise 1: File Permissions with chmod

**Objective**: Practice changing file permissions using symbolic and numeric notation.

**Setup**:
```bash
# Create practice files
mkdir ~/prog71040
mkdir ~/prog71040/security_lab
cd ~/prog71040/security_lab
echo "This is a secret document" > secret.txt
echo "#!/bin/bash\necho 'Hello World'" > myscript.sh
echo "Public information here" > public.txt
```

**Tasks**:
1. Check current permissions: `ls -l`
2. Make `secret.txt` readable only by owner: `chmod 600 secret.txt`
3. Make `public.txt` readable by everyone: `chmod 644 public.txt`
4. Make `myscript.sh` executable: `chmod +x myscript.sh`
5. Set `myscript.sh` to be executable by owner, readable by group: `chmod 740 myscript.sh`
6. Remove all permissions for others on `secret.txt`: `chmod o-rwx secret.txt`

**Verification**: Use `ls -l` after each change to see the permission changes.

---

## Exercise 2: Group Management with chgrp

**Objective**: Practice changing group ownership of files and directories.

**Setup**:
```bash
# Create test files and check available groups
cd ~/prog71040/security_lab
touch group_file1.txt group_file2.txt
mkdir shared_folder
echo "Shared document" > shared_folder/team_doc.txt
groups  # See what groups you belong to
```

**Tasks**:
1. Check current group ownership: `ls -lg`
2. Change group of `group_file1.txt` to `users` group: `chgrp users group_file1.txt`
3. Change group of entire `shared_folder` and contents: `chgrp -R users shared_folder`
4. Try changing to a group you don't belong to (observe the error)
5. Verify changes with: `ls -lg`

**Discussion**: Explain why group permissions are important for team collaboration.

---

## Exercise 3: User Ownership with chown

**Objective**: Learn to change file ownership (requires appropriate permissions).

**Setup**:
```bash
cd ~/prog71040/security_lab
touch ownership_test.txt
echo "Testing ownership changes" > ownership_test.txt
ls -l ownership_test.txt
```

**Tasks**:
1. Check current ownership: `ls -l ownership_test.txt`
2. Try to change owner to `root`: `chown root ownership_test.txt` (this will fail - discuss why)
3. Create a file as your user: `touch myfile.txt`
4. Use `sudo` to change owner to `root`: `sudo chown root myfile.txt`
5. Change both owner and group: `sudo chown root:root ownership_test.txt`
6. Change back to your user: `sudo chown $USER:$USER ownership_test.txt`

**Learning Points**: 
- Only root can change ownership to other users
- The importance of the `sudo` command
- Format: `chown user:group filename`

---

## Exercise 4: Switching Users with su and sudo

**Objective**: Practice switching users and executing commands with elevated privileges.

**Setup**:
```bash
# Create a test script that requires root privileges
cd ~/prog71040/security_lab
echo '#!/bin/bash
echo "Current user: $(whoami)"
echo "User ID: $(id -u)"
touch /tmp/test_root_file.txt 2>/dev/null && echo "Created root file successfully" || echo "Permission denied"
' > privilege_test.sh
chmod +x privilege_test.sh
```

**Tasks**:
1. Run the script as regular user: `./privilege_test.sh`
2. Run with sudo: `sudo ./privilege_test.sh`
3. Check who you are: `whoami` vs `sudo whoami`
4. Try to access root's home: `ls /root` (should fail)
5. Try with sudo: `sudo ls /root`
6. Execute a single command as root: `sudo echo "I have root power!" > /tmp/sudo_test.txt`
7. Check the file: `ls -l /tmp/sudo_test.txt`

**Note**: Demonstrate the difference between `su` (if available) and `sudo`

**Safety Reminder**: Always be careful with sudo - great power, great responsibility!

---

## Exercise 5: Comprehensive Security Scenario

**Objective**: Combine all commands in a realistic scenario.

**Scenario**: You're setting up a shared project directory for a development team.

**Setup**:
```bash
cd ~
sudo mkdir /opt/team_project
```

**Tasks**:
1. **Create the project structure**:
   ```bash
   sudo mkdir ~/prog71040/security_lab/team_project/{docs,scripts,logs}
   sudo touch ~/prog71040/security_lab/team_project/docs/README.md
   sudo touch ~/prog71040/security_lab/team_project/scripts/deploy.sh
   sudo touch ~/prog71040/security_lab/team_project/logs/system.log
   ```

2. **Set appropriate ownership**:
   ```bash
   sudo chown -R $USER:users ~/prog71040/security_lab/team_project
   ```

3. **Set directory permissions**:
   ```bash
   sudo chmod 755 ~/prog71040/security_lab/team_project
   sudo chmod 755 ~/prog71040/security_lab/team_project/{docs,scripts,logs}
   ```

4. **Set file permissions**:
   ```bash
   # Documentation - readable by all team members
   chmod 644 ~/prog71040/security_lab/team_project/docs/README.md
   
   # Scripts - executable by owner, readable by group
   chmod 750 ~/prog71040/security_lab/team_project/scripts/deploy.sh
   
   # Logs - writable by group for logging
   chmod 664 ~/prog71040/security_lab/team_project/logs/system.log
   ```

5. **Verify the setup**:
   ```bash
   ls -la ~/prog71040/security_lab/team_project/
   ls -la ~/prog71040/security_lab/team_project/docs/
   ls -la ~/prog71040/security_lab/team_project/scripts/
   ls -la ~/prog71040/security_lab/team_project/logs/
   ```

6. **Test permissions**:
   ```bash
   # Test writing to README
   echo "# Team Project" >> ~/prog71040/security_lab/team_project/docs/README.md
   
   # Test script execution
   echo "echo 'Deploy script executed'" >> ~/prog71040/security_lab/team_project/scripts/deploy.sh
   /opt/team_project/scripts/deploy.sh
   
   # Test log writing
   echo "$(date): System initialized" >> ~/prog71040/security_lab/team_project/logs/system.log
   ```

**Discussion Points**:
- Why different permission levels for different types of files?
- How does group ownership facilitate teamwork?
- When should you use `sudo` vs regular commands?

---

## Assessment Checklist

For each exercise, students should be able to:

- [ ] **chmod**: Change permissions using both symbolic (rwx) and numeric (755) notation
- [ ] **chgrp**: Change group ownership and understand group-based permissions
- [ ] **chown**: Change user ownership and understand the need for sudo
- [ ] **sudo**: Execute commands with elevated privileges safely
- [ ] **su**: Understand the difference between su and sudo (if available)

## Safety Reminders

1. **Always double-check sudo commands** - they have system-wide impact
2. **Use `ls -l` frequently** to verify permission changes
3. **Work in practice directories** - don't modify system files
4. **Ask for help** if you're unsure about a command's impact
