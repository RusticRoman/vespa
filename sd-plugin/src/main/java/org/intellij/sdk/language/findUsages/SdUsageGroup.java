package org.intellij.sdk.language.findUsages;

import com.intellij.navigation.ItemPresentation;
import com.intellij.navigation.NavigationItemFileStatus;
import com.intellij.openapi.util.NlsSafe;
import com.intellij.openapi.util.text.StringUtil;
import com.intellij.openapi.vcs.FileStatus;
import com.intellij.openapi.vfs.VirtualFile;
import com.intellij.psi.SmartPointerManager;
import com.intellij.psi.SmartPsiElementPointer;
import com.intellij.usages.UsageGroup;
import org.intellij.sdk.language.psi.SdDeclaration;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.swing.*;

public class SdUsageGroup implements UsageGroup {
    private final VirtualFile myFile;
    private final SmartPsiElementPointer<SdDeclaration> myElementPointer;
    private final String myText;
    private final Icon myIcon;

    public SdUsageGroup(SdDeclaration element) {
        myFile = element.getContainingFile().getVirtualFile();
        myText = StringUtil.notNullize(element.getName());
        myElementPointer = SmartPointerManager.getInstance(element.getProject()).createSmartPsiElementPointer(element);
        ItemPresentation presentation = element.getPresentation();
        myIcon = presentation != null ? presentation.getIcon(true) : null;
    }
    
    @Override
    public boolean isValid() {
        SdDeclaration element = myElementPointer.getElement();
        return element != null && element.isValid();
    }
    
    @Override
    public void navigate(boolean requestFocus) {
        final SdDeclaration nameElement = myElementPointer.getElement();
        if (nameElement != null) {
            nameElement.navigate(requestFocus);
        }
    }
    
    @Override
    public boolean canNavigate() {
        return isValid();
    }

    @Override
    public boolean canNavigateToSource() {
        return canNavigate();
    }

    @Override
    public int compareTo(@NotNull UsageGroup usageGroup) {
        return getPresentableGroupText().compareToIgnoreCase(usageGroup.getPresentableGroupText());
    }
    
    @Override
    public boolean equals(Object object) {
        if (object instanceof SdUsageGroup) {
            final SdUsageGroup other = (SdUsageGroup) object;
            return myFile.equals(other.myFile) && myText.equals(other.myText);
        }
        return false;
    }
    
    @Override
    public FileStatus getFileStatus() {
        return isValid() ? NavigationItemFileStatus.get(myElementPointer.getElement()) : null;
    }
    
    @Override
    public int hashCode() {
        return myText.hashCode();
    }

    @Override
    public @NotNull String getPresentableGroupText() {
        return myText;
    }
    
    @Override
    public @Nullable Icon getIcon() {
        return myIcon;
    }
}
